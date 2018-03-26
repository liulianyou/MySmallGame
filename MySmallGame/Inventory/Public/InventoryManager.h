/* 
* Author:	Kayak_Liulianyou;
* Time:		2018/2/2
* Purpose: 
*			You can treat this class as factory class which will maintain all items
*			One Player just has one InventoryManager's instance to manage all items, and this class is just like one component in each character
*			I don't define the InventoryManager as Commponet is due to the Component is one more heavy things and each pawn no mater the palyer or the AI pawn(NPC)
*			they all have one invtoryManager, the difference betwenn them is just the content is different.So we don't need to change it according to different pawn type
*
*/
#pragma once

//Engine Core Head:Contained all marco that used in UObject
#include "UObject/ObjectMacros.h"

//Local include
#include "InventoryDefination.h"
#include "ItemActorBase.h"

//Generated file included
#include "InventoryManager.generated.h"

class UItemBase;


/*
* The slot that one character to equip some itemActor
* The enumerators in this enumeration will always show the items equipped on that slot
*/
UENUM(BlueprintType, Meta = (BitFlags))
enum EEquipSlot
{
	EEquipSlot_Head					UMETA(DisplayName = "Head"),
	EEquipSlot_Shoulder				UMETA(DisplayName = "Shoulder"),
	EEquipSlot_Neck					UMETA(DisplayName = "Neck"),
	EEquipSlot_Chest				UMETA(DisplayName = "Coat"),
	EEquipSlot_LeftHand				UMETA(DisplayName = "Left Hand"),
	EEquipSlot_RightHand			UMETA(DisplayName = "Right Hand"),
	EEquipSlot_Legd					UMETA(DisplayName = "Leg"),
	EEquipSlot_Foot					UMETA(DisplayName = "Foot"),

	//Reserve to calculate the max number of this enumeration
	EEquipSlot_MAX				UMETA(Displayname = "Max Count")
};



UCLASS(Config=Item)
class KAYAKGAME_API UInventoryManager : public UObject
{
public:
	GENERATED_UCLASS_BODY()

	
	/*
	* AS Unreal Engine 4 will instance each class derived from UObjec in the memory used to store the information of each class.
	* We can't use the default construct function to construct this class, so use this function if need to initialize one instance.
	*/
	void Initialize( const UObject* owner ){}

	/*
	* Befroe we delete the instance we should first finalize all the content in it
	*/
	void Finalize() {}


#pragma region GetPropertyFunction
	FORCEINLINE INT GetMaxBagSize() const { return m_maxBagSize; }

#pragma endregion GetPropertyFunction

#pragma region SetPropertyFunction

	FORCEINLINE void SetMaxBagSize(INT size) { m_maxBagSize = size; }

#pragma endregion SetPropertyFunction

	/*
	* The play send command to use the specific items.The same as   UseItem( FString itemGUID, INT num )
	*
	* @param	item	the specific item to be used
	* @param	num		the number that should be used, if the property m_Stackable is false or the m_MaxStackNum is 1 this parameter num will be ignored
	*/
	void UseItem( UItemBase* item, INT num = -1 ) {}

	/*
	* The play send command to use the specific items.
	*
	* @param	itemID	the item withe the specific ItemID to be used
	*					At some situations different items may have the same ItemID but the ItemGUID is different as the stackable is false or the maxStackNum is 1.
	* @param	num		if is the default number -1, this will use all the items with the ItemID, regardless with the different ItemGUID,
	*					if the number is larger than one we will use min value between the num parameter and the number of each item with the same id but different Guid  
	*/
	void UseItem( INT ItemID, INT num = -1 ) {}


	/*
	* The play send command to use the specific items.The same as  UseItem( UItemBase* item, INT num = -1 )
	*
	* @param	item	the specific item to be used
	* @param	num		the number that should be used, if the property m_Stackable is false or the m_MaxStackNum is 1 this parameter num will be ignored
	*/
	void UseItem( FString itemGUID, INT num = 1 ){}

	/*
	* Delete the target item
	* 
	* @Param	Item	the target item we should delete
	* @param	num		the number that should delete, if the property m_Stackable is false or the m_MaxStackNum is 1 this parameter num will be ignored
	*/
	void DeleteItem(UItemBase* Item, INT num = 1) {}

	/*
	* Delete item with the specific ItemID
	*
	* @param	ItemID	the target Item's ID
	* @param	num		the number of item to be deleted.if is the default number -1, this will use all the items with the ItemID, regardless with the different ItemGUID,
	*					if the number is larger than one, the min value we will delete is between the num parameter and the number of each item with the same id but different Guid  
	*/
	void DeleteItem(INT ItemID, INT num = -1) {}

	/*
	* Delete item with the specific ItemGUID
	*
	* @param	ItemGUID	the target Item's ItemGUID
	* @param	num the		number that should be deleted, if the property m_Stackable is false or the m_MaxStackNum is 1 this parameter num will be ignored
	*/
	void DeleteItem(FString ItemGUID, INT num = 1) {}

	/*
	* Create Item through ItemBase's type
	*/
	template<typename ItemBaseClass>
	UItemBase* CreateItem( struct FItemBaseMiniRecoverInfo* itemMiniInfo ) { return CreateItem(ItemBaseClass::StaticClass(), itemMiniInfo); }

	/*
	* Create Item by the minialize recover information
	*/
	UItemBase* CreateItem(const TSubclassOf<UItemBase> itemClass, struct FItemBaseMiniRecoverInfo* itemMiniInfo) { return nullptr; }
	
	template<typename ItemActorBaseClass>
	AItemActorBase* CreateItemActor() { return CreateItemActor(ItemActorBaseClass::StaticClass); }

	/*
	* Create ItemActor by the target UClass which stands for all the classes derived from AItemActorBase
	*/
	AItemActorBase* CreateItemActor(TSubclassOf<AItemActorBase> ItemActorNativeClass) { return nullptr; }

protected:


private:

	//The owner of this class instance. 
	TSharedPtr<UObject> m_pOwner;

	//Store all items which derived from UItemBase
	TArray<UItemBase*> m_ItemList;

	//Store all items which derived from AItemActorBase,
	//The difference between m_ItemActorList and m_EquipmentList is ItemActorList is just used to show the outlook in one character such as the fashion cloth,
	//and the EquipmentList is the actual items which will affect the character ability.
	TMap<EEquipSlot,AItemActorBase*> m_ItemActorList;

	//Store the actual equipped actors which will affect the character's ability
	//The difference between m_ItemActorList and m_EquipmentList is ItemActorList is just used to show the outlook in one character such as the fashion cloth,
	//and the EquipmentList is the actual items which will affect the character ability.
	TMap<EEquipSlot, AItemActorBase*> m_EquipmentList;

	//The max size of bag in this Inventory of each character
	INT m_maxBagSize;

};