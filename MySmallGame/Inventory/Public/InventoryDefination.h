/*
* Author: Kayak_Liulianyou
* Time: 2018/1/29
* Purpose: This file will contain all enumerations, marco or any other definitions which will be used in inventory feature.
*		   
*
*
*/
#pragma once

#include "UObject/ObjectMacros.h"

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
*		|	  +---- EMeeleType
*		|	  	  		EMeeleType_Nife
*		|	  			EMeeleType_Axe
* 		|	  			EMeeleType_Sword
* 		|
* 		+---- EVehicleType		
* 		|		EVehicleType_Car
* 		|		EVehicleType_Airplane
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
	EInventroyType_Consumable	UMETA( Displayname = "Consumable Type" ),

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
	EConsumableType_Capsule = EInventroyType::EInventroyType_MAX + 1					UMETA( Displayname = "Blood Pack" ),

	//Items which will be used in the Gun
	EConsumableType_Bullet																UMETA( Displayname = "Bullet" ),

	//Reserve to calculate the max number of this enumeration
	EConsumableType_Max																	UMETA(Displayname = "Max Count")
};

//Total types which items can't be consumed
UENUM(BlueprintType, Meta = (BitFlags))
enum EUnconsumableType
{
	EUnconsumableType_Euipment = EInventroyType::EInventroyType_Unconsumable * 10000 		UMETA(DisplayName = "Equipment"),

	EUnconsumableType_Weapon															UMETA(DisplayName = "Weapon"),

	EUnconsumableType_Vehicle															UMETA(DisplayName = "Vehicle"),

	//Reserve to calculate the max number of this enumeration
	EUnconsumableType_Max																UMETA(DisplayName = "Max Count")
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
UENUM( BlueprintType, Meta = (BitFlags) )
enum EWeaponType
{
	EWeaponType_LMG	 = EUnconsumableType::EUnconsumableType_Max 	UMETA( Displayname = "LMG" ),		//Light Machine Gun
	EWeaponType_AR																			UMETA( DisplayName = "AR" ),		//Assault Rifle
	EWeaponType_GRENADA																		UMETA( Displayname = "Grenada"),	
	EWeaponType_HG																			UMETA( Displayname = "HG"),			//
	EWeaponType_HMG																			UMETA( Displayname = "HMG"),
	EWeaponType_FT																			UMETA( Displayname = "FT"),
	EWeaponType_RL																			UMETA( Displayname = "RL"),
	EWeaponType_SG																			UMETA( Displayname = "SG"),
	EWeaponType_SMG																			UMETA( Displayname = "SMG"),		//Small Machine Gun 
	EWeaponType_SR																			UMETA( Displayname = "SR"),			//Snipe rife
	//Reserve to calculate the max number of this enumeration
	EWeaponType_Max																			UMETA( Displayname = "Max Count")
};	

//Accessories' type
UENUM(BlueprintType, Meta = (BitFlags))
enum EAccessoryType
{
	EAccessoryType_BARREL = 1		UMETA(Displayname = "Barrel"),
	EAccessoryType_MAGAZINE			UMETA(Displayname = "Magizine"),
	EAccessoryType_SILENCER			UMETA(Displayname = "Silencer"),
	EAccessoryType_PAINT			UMETA(Displayname = "Paint"),
	//Reserve to calculate the max number of this enumeration
	EAccessoryType_Max				UMETA(Displayname = "Max Count")
};

