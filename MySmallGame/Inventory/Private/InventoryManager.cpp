#include "../Public/InventoryManager.h"

//Engine include: Internet interface
#include "Net/UnrealNetwork.h"

//Local Include
#include "../Public/ItemBase.h"
#include "../Public/ItemActorBase.h"


UInventoryManager::UInventoryManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	m_pOwner(nullptr),
	m_ItemList(TArray<UItemBase*>()),
	m_ItemActorList(TMap<EEquipSlot, AItemActorBase*>()),
	m_EquipmentList(TMap<EEquipSlot, AItemActorBase*>()),
	m_maxBagSize(0)
{

}

void UInventoryManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInventoryManager, m_pOwner);
}

AItemActorBase* UInventoryManager::CreateitemActor(INT ItemID, TSharedPtr<UObject> owner)
{
	//Get Item's simple information form server according to ItemID
	FItemBaseMiniRecoverInfo* ItemMiniRecoverInfo;
	//Create one ItemBase which will be used to create
	UItemBase* ItemBase = NewObject<UItemBase>();
	ItemBase->SetOwner(owner.Get());
	ItemBase->SetMinimumInfo(ItemMiniRecoverInfo);
	ItemBase->GetRealWorldItemClassName();

	ItemBase->ConditionalBeginDestroy();



}




