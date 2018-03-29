
#include "../Public/ItemBase.h"

#include "Engine/DataTable.h"
#include "Engine/DataTableCSV.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

UDataTable* UItemBase::s_ItemSimpleInfoBuffer = nullptr;

UItemBase::UItemBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	m_pOwner(nullptr),
	m_BindActorItemClassName(""),
	m_ItemID(-1),
	m_ItemNameLabel(FString("")),
	m_ItemDescriptionLabel(FString("")),
	m_NeedToUpdateContent(false)
{
	//Put it here so that the static members ItemSimpleInfo can be initialized when the engine is starting.
	UItemBase::InitSimpleDataInfo();

}

void UItemBase::SetMinimumInfo( const FItemBaseMiniRecoverInfo* itemMiniData)
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
	const FItemSimpleInfo* ItemSimpleInfo = UItemBase::GetItemSimpleInfoByItemID( m_ItemID );

	if (ItemSimpleInfo == nullptr)
	{
		//Should do some exception handle here
		return;
	}

	m_ItemNameLabel = ItemSimpleInfo->ItemNameLabel;
	m_ItemDescriptionLabel = ItemSimpleInfo->ItemDescriptionLabel;
	m_ItemIconInfo = ItemSimpleInfo->ItemIcon;
}


void UItemBase::UpdateContent()
{
	if (!m_NeedToUpdateContent) return;

	m_NeedToUpdateContent = false;

}


void UItemBase::InitSimpleDataInfo()
{
	if (s_ItemSimpleInfoBuffer != nullptr ) return;
	
	s_ItemSimpleInfoBuffer = NewObject<UDataTable>();

	s_ItemSimpleInfoBuffer->RowStruct = FItemSimpleInfo::StaticStruct();

	FString CSVString;
	if (!FFileHelper::LoadFileToString(CSVString, *(FPaths::ProjectDir() / TEXT("Config/ItemSimpleInfo.csv"))))
	{
		//Should do some exception hand here
		return;
	}
	TArray<FString> Problems;

	FDataTableImporterCSV(*s_ItemSimpleInfoBuffer,CSVString, Problems).ReadTable();

	if (Problems.Num() != 0)
	{
		//Should do some exception hand here
		return;
	}

}

const FItemSimpleInfo* UItemBase::GetItemSimpleInfoByItemID(INT ItemID)
{
	for (auto it : UItemBase::s_ItemSimpleInfoBuffer->RowMap)
	{
		FItemSimpleInfo* itemInfo = reinterpret_cast<FItemSimpleInfo*> (it.Value);
		if (itemInfo->ItemID == ItemID)
		{
			return itemInfo;
		}
	}

	return nullptr;
}
