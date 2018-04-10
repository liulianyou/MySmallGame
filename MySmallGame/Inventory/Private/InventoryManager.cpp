#include "../Public/InventoryManager.h"

//Engine include: Internet interface
#include "Net/UnrealNetwork.h"
#include "OnlineSubsystem.h"
//Engine include: File System
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Engine/DataTable.h"
#include "Engine/DataTableCSV.h"

//Local Include
#include "../Public/ItemBase.h"
#include "../Public/ItemActorBase.h"


DEFINE_LOG_CATEGORY(LogInventory);

UDataTable* UInventoryManager::s_ItemBaseDataTable = nullptr;

UInventoryManager::UInventoryManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	m_ItemList(TArray<UItemBase*>()),
	m_ItemActorList(TMap<EEquipSlot, AItemActorBase*>()),
	m_EquipmentList(TMap<EEquipSlot, AItemActorBase*>()),
	m_maxBagSize(0)
{

	UInventoryManager::InitTotalItemInfo();

}

/*
* As the InventoryManager is the one compoenent and it should be replicated stand along, so we should register the replicated properties here
*
* When you create new subObject with InventoryManager in other Object you should call function SetIsReplicated(true), 
* more details see : https://docs.unrealengine.com/en-US/Gameplay/Networking/Actors/Components
*/
void UInventoryManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInventoryManager, m_maxBagSize);
}

TArray<AItemActorBase*> UInventoryManager::CreateItemActor(INT ItemID, UObject* Owner, INT Number)
{
	TArray<AItemActorBase*> result;

	FItemBaseInfo* ItemFullInfo = GetItemInfo(ItemID);
	check(ItemFullInfo);

	ItemFullInfo->CreateTime = FApp::GetCurrentTime();
	for (int i = 0; i < Number; i++)
	{
		//As ItemActor can be showed in the world so the enterties of the same templete should have different GUID to disinteguish them.
		ItemFullInfo->ItemGUID = FGuid::NewGuid().ToString();

		result.Emplace(AItemActorBase::CreateItemActor(ItemFullInfo, Owner));

		ClientDoCreateItemActor(ItemFullInfo->CreateJsonStringForAttributs(), Owner);
	}

	return result;
}

void UInventoryManager::ClientDoCreateItemActor_Implementation(const FString& ItemAttributesJsonValue, UObject* owner, INT Number = 1)
{
	int a = 0;
	a++;
}

FItemBaseInfo* UInventoryManager::GetItemInfo(int ItemID)
{
	for (auto it : s_ItemBaseDataTable->RowMap)
	{
		FItemBaseInfo* itemFullInfo = reinterpret_cast<FItemBaseInfo*>(it.Value);
		if (itemFullInfo->ItemID == ItemID)
		{
			return itemFullInfo;
		}
	}

	return nullptr;
}

//This function will not have any effect in client side
void UInventoryManager::InitTotalItemInfo()
{
	if (s_ItemBaseDataTable != nullptr) return;

	bool CanInit = false;

	//Make should this function only work in Server side or in PIE which is not in client mode,
	//As this function is call in construction of this class and when UE4 preInit it will instance all the function which is refected in building, 
	//at that time the Net and other game mode may be not be initialized, we just can use the golobal variable to identify which mode is current engine running.
	if(GIsClient ) CanInit = false;
	if(GIsServer || (GIsEditor&&GIsClient))  CanInit = true;

	if (!CanInit) return;

	ReadCSVConfigFile(*(FPaths::ProjectDir() / TEXT("Config/ItemBaseInfo.csv")), FItemBaseInfo::StaticStruct());



}

void UInventoryManager::ReadCSVConfigFile(FString path, UStruct* structInfo)
{
	s_ItemBaseDataTable = NewObject<UDataTable>();

	s_ItemBaseDataTable->RowStruct = dynamic_cast<UScriptStruct*>(structInfo);

	if (s_ItemBaseDataTable->RowStruct == nullptr)
	{
		UE_LOG(LogInventory, Error, TEXT("Make sure the target struct %s is the substruct of UScriptStruct "), *structInfo->GetName());
		return;
	}

	FString CSVString;
	if (!FFileHelper::LoadFileToString(CSVString, *path))
	{
		UE_LOG(LogInventory, Error, TEXT("Cann't open file %s when reading csv config file in invnetory manager; "), *path);
		return;
	}
	TArray<FString> Problems;
	Problems = s_ItemBaseDataTable->CreateTableFromCSVString(CSVString);


	if (Problems.Num() != 0)
	{
		UE_LOG(LogInventory, Error, TEXT("When to process csv config file %s there are %d problems: "), *path, Problems.Num());
		for (int i = 0; i < Problems.Num() ;i++)
		{
			UE_LOG(LogInventory, Error, TEXT("(%d)_______________________________%s; "), (i + 1), *Problems[i]);
		}
		return;
	}
}





