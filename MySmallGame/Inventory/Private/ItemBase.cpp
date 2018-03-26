
#include "../Public/ItemBase.h"

UItemBase::UItemBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	m_pOwner(nullptr),
	m_BindActorItemClassName(""),
	m_ItemID(-1),
	m_ItemNameLabel(FString("")),
	m_ItemDescriptionLabel(FString("")),
	m_NeedToUpdateContent(false)
{

}

void UItemBase::InitializeContent( const FItemBaseMiniRecoverInfo* itemMiniData)
{

	if (itemMiniData->ItemID		!= m_ItemID			&&
		itemMiniData->ItemGUID		!= m_ItemGUID		&&
		itemMiniData->DurationTime	!= m_DurationTime	&&
		itemMiniData->CreateTime	!= m_CreateTime		&&
		itemMiniData->ItemType		!= m_ItemType		)
	{
		m_NeedToUpdateContent = true;
	}

	m_ItemID = itemMiniData->ItemID;
	m_ItemGUID = itemMiniData->ItemGUID;
	m_DurationTime = itemMiniData->DurationTime;
	m_CreateTime = itemMiniData->CreateTime;
	m_ItemNumber = itemMiniData->ItemNumber;
	m_ItemType = itemMiniData->ItemType;
		
	//Read from local config file which only contains the item's ID, label name, description name label
	m_ItemNameLabel = "";
	m_ItemDescriptionLabel = "";
	//m_ItemIconInfo = 
	//m_ItemType = 

}


void UItemBase::UpdateContent()
{
	if (!m_NeedToUpdateContent) return;



}