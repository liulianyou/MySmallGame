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


UDataTable* UInventoryManager::s_TotalItemDataTable = nullptr;

UInventoryManager::UInventoryManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	m_pOwner(nullptr),
	m_ItemList(TArray<UItemBase*>()),
	m_ItemActorList(TMap<EEquipSlot, AItemActorBase*>()),
	m_EquipmentList(TMap<EEquipSlot, AItemActorBase*>()),
	m_maxBagSize(0)
{

	UInventoryManager::InitTotalItemInfo();

}

void UInventoryManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInventoryManager, m_pOwner);
}

AItemActorBase* UInventoryManager::ServerCreateItemActor(INT ItemID, UObject* owner)
{
	//Get Item's simple information form server according to ItemID
	FItemBaseMiniRecoverInfo* ItemMiniRecoverInfo = nullptr;
	//Create one ItemBase which will be used to create
	UItemBase* ItemBase = NewObject<UItemBase>();
	ItemBase->SetOwner(owner);
	ItemBase->SetMinimumInfo(ItemMiniRecoverInfo);
	ItemBase->GetRealWorldItemClassName();

	ItemBase->ConditionalBeginDestroy();


	return nullptr;
}

//This function will not have any effect in client side
void UInventoryManager::InitTotalItemInfo()
{
	if (s_TotalItemDataTable != nullptr) return;

	bool CanInit = false;

	if(GIsClient ) CanInit = false;
	if(GIsServer || (GIsEditor&&GIsClient))  CanInit = true;

	if (!CanInit) return;

	s_TotalItemDataTable = NewObject<UDataTable>();
	 
	s_TotalItemDataTable->RowStruct = FItemFullInfo::StaticStruct();

	FString CSVString;
	if (!FFileHelper::LoadFileToString(CSVString, *(FPaths::ProjectDir() / TEXT("Config/ItemFullInfo.csv"))))
	{
		//Should do some exception handler here
		return;
	}
	TArray<FString> Problems;
	Problems = s_TotalItemDataTable->CreateTableFromCSVString(CSVString);

	for (auto it : s_TotalItemDataTable->RowMap)
	{
		FItemFullInfo* itemFullInfo = reinterpret_cast<FItemFullInfo*>(it.Value);
		int a = 0;
	}

	if (Problems.Num() != 0)
	{
		//Should do some exception handler here
		return;
	}
}




