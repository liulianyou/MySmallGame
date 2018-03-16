/* 
* Author: Kayak_Liulianyou;
* Time: 2018/2/2
* Purpose: 
*			You can treat this class as factory class which will maintain all items
*
*
*/
#pragma once

//Engine Core Head:Contained all marco that used in UObject
#include "UObject/ObjectMacros.h"

//Local include
#include "InventoryDefination.h"

//Generated file included
#include "InventoryManager.generated.h"

class UItemBase;

UCLASS(Config=Item)
class UInventoryManager : public UObject
{
public:
	GENERATED_UCLASS_BODY()

	/* 
	* Create Item through item type
	*  
	* @param createItemActor true means it will spawn the actor in the real world, false it just create ItemBaseComponent.
	* @param ... the variable argument stands for the target item's type. 
	*			 each value stands for the one hierarchy of the item's tree.
	*			 Such as when we want to create one LMG weapon we should use this function like
	*			 CreateItem( true, INVENTORY_USEABLE_EFFECT, EUsableEffectGamePlayType_Weapon, EWeaponType_LMG );
	*/
	void CreateItem(bool createItemActor, ...) {};


protected:

	void RegisterItemClass() {};


private:
};