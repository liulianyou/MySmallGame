/*
* Author:	Kayak_Liulianyou
* Time:		2018/1/29
* Purpose:	The base abstract class of item in our games.
*			all the class derived from this class is used to restore the Items
*		   
*/

#pragma once

//Engine Core Head:Contained all marco that used in UObject
#include "UObject/ObjectMacros.h"

//Local include
#include "InventoryDefination.h"
#include "ItemActorBase.h"

//Automatically generated head file
#include "ItemBase.generated.h"


UCLASS(Config = Item)
class KAYAKGAME_API UItemBase : public UObject
{
	GENERATED_UCLASS_BODY()



public:
#pragma region ProperitiesGet
	UFUNCTION(BlueprintCallable, Category = "Kayak|Item|Base" )
	FItemTypeHierarchy GetItemType() const { return m_ItemType; }

	UFUNCTION(BlueprintCallable, Category = "Kayak|Item|Base")
	FString GetBindItemActorClassName() const { return m_BindActorItemClassName; }

	UFUNCTION(BlueprintCallable, Category = "Kayak|Item|Base")
	FIconDetails GetIconInfo() const { return m_ItemIconInfo; }

	UFUNCTION(BlueprintCallable, Category = "Kayak|Item|Base")
	FString GetItemNameLabel() const { return m_ItemNameLabel; }

	UFUNCTION(BlueprintCallable, Category = "Kayak|Item|Base")
	FString GetItemDescriptionLabel() const { return m_ItemDescriptionLabel; }

	UFUNCTION(BlueprintCallable, Category = "Kayak|Item|Base")
	INT GetItemId() const { return m_ItemID; }

	UFUNCTION(BlueprintCallable, Category = "Kayak|Item|Base")
	FString GetItemGUID() const { return m_ItemGUID; }


	/*
	* Get all the data table of simple information
	*/
	static UDataTable* GetItemSimpleInfoDataTable() { return UItemBase::s_ItemSimpleInfoBuffer; }

	/*
	* I don't find any function in TMap that can use lambada so Use this function to get ItemSimpleInfo;
	*/
	static const FItemSimpleInfo* GetItemSimpleInfoByItemID(INT ItemID);

#pragma endregion ProperitiesGet


#pragma region ProperitiesSet

	void SetOwner(UObject* owner) { m_pOwner = owner; };

	/*
	* Set the default minimum information of item.
	* When the server create new item or transfer one item to client, they first transfer the mini data to reduce the bindwidth,
	* If the client need the full inforamtion of Item, the client should use the UpdateContent() to get all information
	*/
	virtual void SetMinimumInfo(const FItemBaseMiniRecoverInfo* itemBaseRecoverInfo);

#pragma endregion ProperitiesSet

	/*
	* Get the full information of this item from the server.
	*/
	virtual void UpdateContent();

	//Interface for the player to do interaction with this item
	virtual void Use() {};
	virtual void Delete() {};
	virtual void DropFromBag() {};
	virtual void Disintegrage() {};

	/*
	* Try to update the attributs which need to request value from server
	*
	* @param	JsonString	String with the JSON format. 
	*						this value contans all the data that the client cann't read from local drectly.
	*/
	virtual void UpdateAttributsFromJsonString(FString JsonString);

	/** This signifies the attribute set can be ID'd by name over the network. */
	void SetNetAddressable();

	bool IsNameStableForNetworking() const override;

	bool IsSupportedForNetworking() const override{ return true; }

	UFUNCTION(Client, Reliable)
	void DoSomething( int debugValue );

	UPROPERTY(Replicated)
	int DebugNetValue;

protected:

private:

	/*
	* Get config value from different config files suchas CSV files, json files;
	*/
	static void InitSimpleDataInfo();

private:

	//ID of Item
	uint32 m_ItemID;

	//The unique identification of the Item.
	UPROPERTY(Transient)
	FString m_ItemGUID;

	//Flag to check weather this item's content has been updated.
	//By default we just initialize the attributs by the FItemBaseMiniRecoverInfo, and other attributs we wouldn't to transfer to client when the item is first build.
	UPROPERTY(Transient)
	bool m_NeedToUpdateContent;

	//The name of this , the actual item's name should be read from the localization system which will use this value as key value
	FString m_ItemNameLabel;

	//Short description of this item, the actual description should be read through the localization system which will use this value as key value
	FString m_ItemDescriptionLabel;

	//represent for the item's icon which will be showed in the UI
	FIconDetails m_ItemIconInfo;

	//The owner of this class instance; mostly it refers to the pawn who owned it.
	UPROPERTY(Transient)
	UObject* m_pOwner;

	//The target ItemActor that this Item refer to.
	UPROPERTY(Transient)
	AItemActorBase* m_ItemActor;

	//the class name of items which will used to spawn Actor in the real world.
	FString m_BindActorItemClassName;

	//Default price of this item when the player sell it to NPC, each item's actual price should be change according to its environment.
	//Such as different NPC have different price to pay for the same item. 
	//If this value is -1 which means this item can't be sold, the player only destroy it by delete it if the member m_Deletable is true
	TMap<TEnumAsByte<EItemPriceType>, uint32> m_ItemDefaultPrice;

	//Check weather this item can be deleted by the player.
	//If one item can't be deleted just means the player can't sell it, drop it, or disintegrate it.
	uint32 m_Deleteable : 1;
	
	//Flag to check weather the player can spawn this item with the m_BindActorItemClass.
	uint32 m_CanBeSpawned : 1;

	//Weather this item is stackable 
	uint32 m_Stackable : 1;

	//Try to config weather should delete this item When the player use it create ItemActor in world.
	uint32 m_DeletedAfterSpawnActor : 1;

	//If the value is true means on character in the game only have one instance of the class derived from ItemBase.
	uint32 m_IsUnique : 1;

	//Millisecond to represent the total duration time of this item
	//-1 means the owner can own this item for ever
	double m_DurationTime;

	//Millisecond to represent for creation time.
	double m_CreateTime;

	//The main type of this item, this value come form the m_ItemType
	FItemTypeHierarchy m_ItemType;

	//the total number of this items
	//If the member m_Stackable is false the max value of this member is 1;
	//If this member's value is zero we should delete this item
	uint32 m_ItemNumber;

	//the max number of this item can be stacked in bag or any other container
	//If the member m_Stackable is false, the max value of this member is 1;
	uint32 m_ItemMaxStackNumber;

	/** Is this Item safe to ID over the network by name?  */
	uint32 m_NetAddressable : 1;

	//Store the simple information of items which is read from /Game/Config/Jason
	static UDataTable* s_ItemSimpleInfoBuffer;

};
