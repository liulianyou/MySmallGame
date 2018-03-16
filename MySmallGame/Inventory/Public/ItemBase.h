/*
* Author: Kayak_Liulianyou
* Time: 2018/1/29
* Purpose: The base abstract class of item in our games.
*		   
*		   
*/

#pragma once

//Engine Core Head:Contained all marco that used in UObject
#include "UObject/ObjectMacros.h"

//Local include
#include "InventoryDefination.h"
#include "UI/UIInterface.h"

//Automatically generated head file
#include "ItemBase.generated.h"


/*
* The hierarchy of item type.
* Total members in this struct is refer to the max hierarchy of item type
*/
USTRUCT(BlueprintType)
struct FItemTypeHierarchy
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY()
		INT FirstLayer;

	UPROPERTY()
		INT SecondLayer;

	UPROPERTY()
		INT ThirdLayer;

	UPROPERTY()
		INT Fourthlayer;

	FItemTypeHierarchy(INT _FirstLayer = -1, INT _SecondLayer = -1, INT _ThirdLayer = -1, INT _FourthLayer = -1) :
		FirstLayer(_FirstLayer),
		SecondLayer(_SecondLayer),
		ThirdLayer(_ThirdLayer),
		Fourthlayer(_FourthLayer)
	{}

	static INT GetHierarchyTreeDeepth()
	{
		static INT hierarchyTreeDeepth = -1;
		if (hierarchyTreeDeepth == -1)
			hierarchyTreeDeepth = sizeof(FItemTypeHierarchy) / sizeof(INT);
		return hierarchyTreeDeepth;
	}
};

UCLASS(Config = Item)
class KAYAKGAME_API UItemBase : public UObject
{
	GENERATED_UCLASS_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "Kayak|Item|Base" )
	const FItemTypeHierarchy& GetItemType() const { return m_ItemType; }

	UFUNCTION(BlueprintCallable, Category = "Kayak|Item|Base")
	const UClass* GetRealWorldItem() const { return m_BindActorItemClass; }

	UFUNCTION(BlueprintCallable, Category = "Kayak|Item|Base")
	const FIconDetails& GetIconInfo() const { return m_ItemIconInfo; }

	UFUNCTION(BlueprintCallable, Category = "Kayak|Item|Base")
	const FString& GetItemNameLabel() const { return m_ItemNameLabel; }

	UFUNCTION(BlueprintCallable, Category = "Kayak|Item|Base")
	const FString& GetItemDescriptionLabel() const { return m_ItemDescriptionLabel; }

	UFUNCTION(BlueprintCallable, Category = "Kayak|Item|Base")
	const INT& GetItemId() const { return m_ItemID; }


	//Interface for the player to do interaction with this item
	virtual void UseItem() {};
	virtual void DeleteItem() {};
	virtual void DropItem() {};
	virtual void PickUpItem() {};
	virtual void DisintegrageItem() {};

protected:

private:

	//ID of Item
	INT m_ItemID;

	//The name of this , the actual item's name should be read through the localization system which will use this value as key value
	UPROPERTY(Config)
	FString m_ItemNameLabel;

	//Short description of this item, the actual description should be read through the localization system which will use this value as key value
	UPROPERTY(Config)
	FString m_ItemDescriptionLabel;

	//The owner of this class instance; mostly it refers to the pawn who owned it.
	APawn* m_pOwner;

	//pointer to the items in the real world which is spawned by this class.
	UClass* m_BindActorItemClass;

	//Default price of this item when the player sell it to NPC, each item's actual price should be change according to its environment.
	//Such as different NPC have different price to pay for the same item. 
	//If this value is -1 which means this item can't be sold, the player only destroy it by delete it if the member m_Deletable is true
	UPROPERTY(Config)
	INT m_ItemDefaultPrice;

	//Check weather this item can be deleted by the player.
	//If one item can't be deleted just means the player can't sell it, drop it, or disintegrate it.
	UPROPERTY(Config)
	bool m_Deleteable;
	
	//Flag to check weather the player can spawn this item with the m_BindActorItemClass.
	bool m_CanBeSpawned;

	//represent for the actual item. 
	UPROPERTY(Config)
	FIconDetails m_ItemIconInfo;

	//The main type of this item, this value come form the m_ItemType
	FItemTypeHierarchy m_ItemType;
};
