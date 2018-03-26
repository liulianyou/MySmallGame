
#pragma once

/*
* Author:	Kayak_Liulianyou
* Time:		2018/3/19
* Purpose:	This class the base class for all items that is spawned in the real work.
*			This class is different from UItemBase class as UItemBase will not create actual actor in real work but this class does
*			The designer can put this class in the real world but UItemBase can not
*/

//Engine Core Head:Contained all marco that used in UObject
#include "UObject/ObjectMacros.h"

//Local include
#include "InventoryDefination.h"
#include "GameFeature/Actor/Public/KayakActorBase.h"
#include "UI/UIInterface.h"

//Generated file included
#include "ItemActorBase.generated.h"

class UItemBase;

UCLASS()
class KAYAKGAME_API AItemActorBase : public AKayakActorBase
{

	GENERATED_UCLASS_BODY()

public:

	/*
	* Initialize form ItemBase Class when the player use the Item through UI which item's type is the children of UItemBase
	*/
	virtual void Initialzie( const UItemBase* ItemBase = nullptr);

protected:



private:

#pragma region SameAsAttribuesInItemBase
	//ID of Item;
	INT m_ItemID;

	//The name of this , the actual item's name should be read from the localization system which will use this value as key value
	FString m_ItemNameLabel;

	//Short description of this item, the actual description should be read through the localization system which will use this value as key value
	FString m_ItemDescriptionLabel;

	//The owner of this class instance; mostly it refers to the pawn who owned it.
	//If this value is nullptr means this item is belong to the level
	APawn* m_pOwner;

	//Default price of this item when the player sell it to NPC, each item's actual price should be change according to its environment.
	//Different NPC have different price to pay for the same item. 
	//If this value is -1 which means this item can't be sold, the player only destroy it by delete it if the member m_Deletable is true
	INT m_ItemDefaultPrice;

	//represent for the item's icon. 
	FIconDetails m_ItemIconInfo;

	//The main type of this item, this value come form the m_ItemType
	FItemTypeHierarchy m_ItemType;
#pragma endregion SameAsAttributesInItemBase

	//refer to the itemBase class, we may use it when the player pick up one ItemActor to his inventory 
	UClass* m_pItemBaseClass;

	//The origin of the item that construct this itemActor
	//If this value is nullptr means this item is belong to the level or the original itemBase should been deleted after the player use the itembase to create it.
	UItemBase* m_pReferencedItem;

	//The absolute path refer to the root file directory of this engine
	FString m_SkeltonMeshPath;

};