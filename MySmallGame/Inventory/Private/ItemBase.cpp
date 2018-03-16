
#include "../Public/ItemBase.h"

UItemBase::UItemBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	m_pOwner(nullptr),
	m_BindActorItemClass(nullptr),
	m_ItemID(-1),
	m_ItemNameLabel(FString("")),
	m_ItemDescriptionLabel(FString(""))
{

}