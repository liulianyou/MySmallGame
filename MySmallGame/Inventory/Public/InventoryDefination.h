/*
* Author:	Kayak_Liulianyou
* Time:		2018/1/29
* Purpose:	This file will contain all enumerations, marco or any other definitions which will be used in inventory feature.
*		   
*
*
*/
#pragma once

//Engine Core Include
#include "UObject/ObjectMacros.h"

//Local include
#include "UI/UIInterface.h"

//Automatically generated head file
#include "InventoryDefination.generated.h"

/*
* The hierarchy of item type.
* Total members in this struct is refer to the max hierarchy of item type
*/
USTRUCT(BlueprintType)
struct FItemTypeHierarchy
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	INT FirstLayer;

	UPROPERTY(EditAnywhere)
	INT SecondLayer;

	UPROPERTY(EditAnywhere)
	INT ThirdLayer;

	UPROPERTY(EditAnywhere)
	INT Fourthlayer;

	FItemTypeHierarchy(INT _FirstLayer = -1, INT _SecondLayer = -1, INT _ThirdLayer = -1, INT _FourthLayer = -1) :
		FirstLayer(_FirstLayer),
		SecondLayer(_SecondLayer),
		ThirdLayer(_ThirdLayer),
		Fourthlayer(_FourthLayer)
	{}

	static INT GetHierarchyTreeDeepth()
	{
		return	sizeof(FItemTypeHierarchy) / sizeof(INT);
	}

	friend bool operator!=(const FItemTypeHierarchy& src, const FItemTypeHierarchy& dest)
	{
		if (dest.FirstLayer != src.FirstLayer	&&
			dest.SecondLayer != src.SecondLayer	&&
			dest.ThirdLayer != src.ThirdLayer	&&
			dest.Fourthlayer != src.Fourthlayer)
			return true;
		else return false;
	}

};



/**
* The hierarchy tree of item's type looks like below:
* EInventoryType 
* |
* +---- EInventroyType_Consumable
* |		|
* |	    +---- EBulletType
* |		|		EBULLETTYPE_LMG
* |		|		EBULLETTYPE_AR
* |		|		EBULLETTYPE_GRENADA
* |		|		EBULLETTYPE_HG
* |		|		EBULLETTYPE_HMG
* |		|		EBULLETTYPE_FT
* |		|		EBULLETTYPE_RL
* |		|		EBULLETTYPE_SG
* |		|		EBULLETTYPE_SMG
* |		|		EBULLETTYPE_SR
* |		|							
* |     +---- ECapsuleType
* |				ECAPSULETYPE_TIME
* |				ECAPSULETYPE_Recharge
* |
* +---- EInventroyType_Unconsumable
* 		|
* 		+---- EWEAPONTYPE
*		|	  |
*		|	  +---- EGunType
*		|     |	  		EWeaponType_LMG
*		|     |			EWeaponType_AR
*		|     |			EWeaponType_GRENADA
*		|     |			EWeaponType_HG
*		|     |			EWeaponType_HMG
*		|     |			EWeaponType_FT
*		|     |			EWeaponType_RL
*		|     |			EWeaponType_SG
*		|     |			EWeaponType_SMG
*		|     |			EWeaponType_SR
*		|	  |
*		|	  +---- EMeleeType
*		|	  	  		EMeleeType_Nife
*		|	  			EMeleeType_Axe
* 		|	  			EMeleeType_Sword
* 		|	  
* 		+---- EAccessoryType
*		|	  |
* 		|	  +----	EAccessoryType_Gun
* 		|	  |			EGunAccessoryType_BARREL	
* 		|	  |			EGunAccessoryType_MAGAZINE	
* 		|     |			EGunAccessoryType_SILENCER	
* 		|	  |			EGunAccessoryType_PAINT	
* 		|	  |
* 		|	  +----	EAccessoryType_Melee
* 		|	  +----	EAccessoryType_Equipment
*		|	  +----	EAccessoryType_Common
* 		|
* 		+---- EVehicleType		
* 		|		EVehicleType_Car
* 		|		EVehicleType_Aircraft
* 		|		EVehicleType_Ship
* 		|
* 		+---- EEquipmentType
*		|		EEquipmentType_Helmet
*		|		EEquipmentType_Glove
*		|		EEquipmentType_Shoulder
*		|		EEquipmentType_Neck
*		|		EEquipmentType_Trouser
*		|		EEquipmentType_Foot
*		|
*		+---- EFashionClothType
*		|		EFashionClothType_FasionTotal
*		|		EFashionClothType_Helmet
*		|		EFashionClothType_Glove
*		|		EFashionClothType_Shoulder
*		|		EFashionClothType_Neck
*		|		EFashionClothType_Trouser
*		|		EFashionClothType_Foot
*		|
*		+---- 	
*/

/*
* This enumeration includes all the categories of item which the player can owned.
* In the item's hierarchy tree this enumeration is the root point, 
* for example we can divide the INVENTORYTYPE_CONSUMBALE to the  blood pack , bullet and so on
*/
UENUM( BlueprintType, Meta = (Bitflags))
enum EInventroyType
{
	//Stands for consumable items such as rechargeable items, bullet, arrows, each capsule which can change into special item and so on.
	//The number of this item will decreased when it is used
	EInventroyType_Consumable		UMETA( Displayname = "Consumable Type" ),

	//Stands for the items which will not disappear when they are used, or some items which can be recycled after been used
	EInventroyType_Unconsumable		UMETA( DisplayName = "Unconsumable type"),

	//Reserve to calculate the max number of this enumeration
	EInventroyType_MAX				UMETA( Displayname="Max Count")
};

//Total types which items is consumable
UENUM(BlueprintType, Meta = (BitFlags))
enum EConsumableType
{
	//Items that create different effect on player or enemy
	EConsumableType_Capsule					UMETA( Displayname = "Blood Pack" ),

	//Items which will be used in the Gun
	EConsumableType_Bullet					UMETA( Displayname = "Bullet" ),

	//Reserve to calculate the max number of this enumeration
	EConsumableType_Max						UMETA(Displayname = "Max Count")
};

//Total types which items can't be consumed
UENUM(BlueprintType, Meta = (BitFlags))
enum EUnconsumableType
{
	//This equipment not include weapon, it just stands for the items that the player wear,
	EUnconsumableType_Euipment  		UMETA(DisplayName = "Equipment"),

	//For the weapons that the player hand 
	EUnconsumableType_Weapon			UMETA(DisplayName = "Weapon"),

	//For all vehicles include car, boat, ship, airplane, and so on.
	EUnconsumableType_Vehicle			UMETA(DisplayName = "Vehicle"),

	//Reserve to calculate the max number of this enumeration
	EUnconsumableType_Max				UMETA(DisplayName = "Max Count")
};

//The capsule type which will contain all the items which the player use it can do some advantage or disadvantage things,
//Such as portion medicament, TimeCapsule and so on
UENUM(BlueprintType, Meta = (BitFlags))
enum ECapsuleType
{
	//Can Recharge the player
	ECapsuleType_Recharge																UMETA( DisplayName = "RchargeCapsule" ),

	//Reserve to calculate the max number of this enumeration
	ECapsuleType_Max																	UMETA(DisplayName = "Max Count")
};


//Weapon's type
UENUM(BlueprintType, Meta = (BitFlags))
enum EWeaponType
{
	//Stands for Gun
	EWeaponType_Gun							UMETA(Displayname = "GUN"),
	
	EWeaponType_Melee						UMETA( DisplayName = "Meele" ),

	//Reserve to calculate the max number of this enumeration
	EWeaponType_Max							UMETA(DisplayName = "Max Count")
};

//Different types of gun in the weapon
UENUM( BlueprintType, Meta = (BitFlags) )
enum EGunType
{
	EGunType_LMG 		UMETA( Displayname = "LMG" ),		//Light Machine Gun
	EGunType_AR			UMETA( DisplayName = "AR" ),		//Assault Rifle
	EGunType_GRENADA	UMETA( Displayname = "Grenada"),	
	EGunType_HG			UMETA( Displayname = "HG"),			//
	EGunType_HMG		UMETA( Displayname = "HMG"),
	EGunType_FT			UMETA( Displayname = "FT"),
	EGunType_RL			UMETA( Displayname = "RL"),
	EGunType_SG			UMETA( Displayname = "SG"),
	EGunType_SMG		UMETA( Displayname = "SMG"),		//Small Machine Gun 
	EGunType_SR			UMETA( Displayname = "SR"),			//Snipe rife
	//Reserve to calculate the max number of this enumeration
	EGunType_Max		UMETA( Displayname = "Max Count")
};	

//Different items can have different accessories to improve their attributes
UENUM(BlueprintType, Meta = (BitFlags))
enum EAccessoryType
{
	//This accessory can be applied for all the below types: Equipments, Weapons, Vehicle
	EAccessoryType_Common		UMETA( DisplayName = "Commone Accessory" ),

	//Accessories only used for Equipment
	EAccessoryType_Equipment	UMETA( DisplayName = "Meele Accessory" ),

	//Accessories only used for gun
	EAccessoryType_Weapon		UMETA( DisplayName = "Weapon Accessory" ),

	//Accessories only used for Vehicle
	EAccessoryType_Vehicle		UMETA( DisplayName = "Vehicle Accessory" ),

	//Reserve to calculate the max number of this enumeration
	EAccessoryType_Max			UMETA(Displayname = "Max Count")

};


//Stands for accessories for weapons, this can include any items that can improve weapons and equipments
//Different weapons has different accessories to improve it 
UENUM(BlueprintType, Meta = (BitFlags))
enum EGunAccessoryType
{
	EGunAccessoryType_BARREL			UMETA(Displayname = "Barrel"),
	EGunAccessoryType_MAGAZINE			UMETA(Displayname = "Magizine"),
	EGunAccessoryType_SILENCER			UMETA(Displayname = "Silencer"),
	EGunAccessoryType_PAINT				UMETA(Displayname = "Paint"),
	//Reserve to calculate the max number of this enumeration
	EGunAccessoryType_Max				UMETA(Displayname = "Max Count")
};



/*
* The minimized data struct that we can use to recover or construct the item with  the content in ItemBase class.
*/
USTRUCT(BlueprintType)
struct FItemBaseMiniRecoverInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	INT ItemID;

	UPROPERTY(EditAnywhere)
	FString ItemGUID;

	UPROPERTY(EditAnywhere)
	INT64 DurationTime;

	UPROPERTY(EditAnywhere)
	INT64 CreateTime;

	UPROPERTY(EditAnywhere)
	INT ItemNumber;

	UPROPERTY(EditAnywhere)
	FItemTypeHierarchy ItemType;

	friend bool operator!=(const FItemBaseMiniRecoverInfo& src, const FItemBaseMiniRecoverInfo& dest)
	{
		if( src.ItemID			!= dest.ItemID			&&
			src.ItemGUID		!= dest.ItemGUID		&&
			src.DurationTime	!= dest.DurationTime	&&
			src.CreateTime		!= dest.CreateTime		&&
			src.ItemNumber		!= dest.ItemNumber		&&
			src.ItemType		!= dest.ItemType		)
		{
			return true;
		}
		else return false;
	}

};

/*
* Minimized information to recover one weapon item
*/
USTRUCT(BlueprintType)
struct FWeaponMiniRecoverInfo : public FItemBaseMiniRecoverInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	INT ItemLevel;
};


/*
* Used to recorder the simple data of items from local csv file.
* As these data is not import adn it will not be transfered from server to client.
*/
USTRUCT()
struct FItemSimpleInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()


	UPROPERTY()
	INT ItemID;

	UPROPERTY()
	FString ItemNameLabel;

	UPROPERTY()
	FString ItemDescriptionLabel;

	UPROPERTY()
	FIconDetails ItemIcon;
};
