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
#include "Json.h"

//Local include
#include "UI/UIInterface.h"

//Automatically generated head file
#include "InventoryDefination.generated.h"

#define GENERATEDENUM(X)	FOREACH_ENUM_##X

#define TOSTRING(X)		#X

#define ENUMSTRING(X)	TOSTRING(X)

#define ENUMERATIONTOSTRING(X)	ENUMSTRING(GENERATEDENUM(X)(""))

/*
* Try to get the actual int value from FString which value is one enumeration
*
* @enumType this value is the capitial enumation type eg. EInventoryType -> EINVENTORYTYPE
* @enumeration the FString of enumeration type eg. EInventoryType_Unconsumable
*/
#define SEARCHINENUMERATION(enumType, enumeration)	\
static FString enumType##StringValue = ENUMERATIONTOSTRING(enumType);\
if (enumType##StringValue.Contains(enumeration))\
{\
	int index = enumType##StringValue.Find(enumeration);\
	int serachStartIndex = INDEX_NONE;\
	int count = INDEX_NONE;\
	do\
	{\
		serachStartIndex = enumType##StringValue.Find("(",ESearchCase::IgnoreCase,ESearchDir::FromStart, serachStartIndex);\
		count++; \
		if( serachStartIndex != INDEX_NONE ) serachStartIndex++;\
		else break;\
		if (serachStartIndex > index) break;\
	}while(serachStartIndex != INDEX_NONE);\
	if (count >= 1) return count - 1;\
}

//Declare the inventory log channel
KAYAKGAME_API DECLARE_LOG_CATEGORY_EXTERN(LogInventory, Log, All);

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


/*
* This struct is used to store the value come from config file;
* Difference between FItemTypeHierarchy and FItemTypeHierarchy is value type in different struct.
* 
* @see FItemTypeHierarchy
*
* I want to exporse the enumeration of different item to designer, so that they can write the enumeration in the config file directly.
* There two addvantages:
*	1): We can read the config file more easily to identify each items type.
*	2): We can maintain the config file more easily when the enumeration's value is changed.
*/

USTRUCT()
struct FItemTypeHierarchyString : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FString FirstLayer;

	UPROPERTY(EditAnywhere)
	FString SecondLayer;

	UPROPERTY(EditAnywhere)
	FString ThirdLayer;

	UPROPERTY(EditAnywhere)
	FString Fourthlayer;
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
* The eunumeration of different type of price.
*/
UENUM(BlueprintType)
enum EItemPriceType
{
	EItemPriceType_Copper				UMETA(Displayname = "Copper"), 
	EItemPriceType_Sliver				UMETA(Displayname = "Sliver"), 
	EItemPriceType_Gold					UMETA(Displayname = "Gold"), 
	EItemPriceType_Diamond				UMETA(Displayname = "Diamond"), 

	//Reserve to calculate the max number of this enumeration
	EItemPriceType_Max				UMETA(Displayname = "Max Count")
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
* Used to recorder the simple data of items from local csv file which the client can read it directly
* As these data is not import adn it will not be transfered from server to client.
*
* Notice: This struct is not the part of struct of FItemBaseInfo, we combine the two struct to represent the total item attributes
*/
USTRUCT()
struct FItemSimpleInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	//@see ItemBase::m_ItemID
	UPROPERTY()
	INT ItemID;

	//@see ItemBase::m_ItemNameLabel
	UPROPERTY()
	FString ItemNameLabel;

	//@see ItemBase::m_ItemDescriptionLabel
	UPROPERTY()
	FString ItemDescriptionLabel;

	//@see ItemBase::m_ItemIcon
	UPROPERTY()
	FIconDetails ItemIcon;
};


typedef TJsonWriterFactory< TCHAR, TCondensedJsonPrintPolicy<TCHAR> > FCondensedJsonStringWriterFactory;
typedef TJsonWriter< TCHAR, TCondensedJsonPrintPolicy<TCHAR> > FCondensedJsonStringWriter;

typedef TJsonWriterFactory< TCHAR, TPrettyJsonPrintPolicy<TCHAR> > FPrettyJsonStringWriterFactory;
typedef TJsonWriter< TCHAR, TPrettyJsonPrintPolicy<TCHAR> > FPrettyJsonStringWriter;

/*
* Used to record the information from the config file which only can be accessed by server, local host, PIE
*/
USTRUCT(BlueprintType)
struct FItemBaseInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	//@see ItemBase::m_ItemID
	UPROPERTY()
	int ItemID;

	//@see ItemBase::m_ItemType
	UPROPERTY()
	FItemTypeHierarchyString ItemType;

	//This property will calcuated from the ItemType in the delegate function: OnPostDataImport
	FItemTypeHierarchy iItemType;

	//@see ItemBase::m_BindActorItemClassName
	UPROPERTY()
	FString	BindActorItemClassName;

	//@see ItemBase::m_ItemDefaultPrice
	UPROPERTY()
	TMap<TEnumAsByte<EItemPriceType>, uint32> ItemDefaultPrice;

	//@see ItemBase::m_Deleteable
	UPROPERTY()
	bool Deleteable;

	//@see ItemBase::m_CanBeSpawned
	UPROPERTY()
	bool CanBeSpawned;

	//@see ItemBase::m_Stackable
	UPROPERTY()
	bool Stackable;

	//@see ItemBase::m_DeletedAfterSpawnActor
	UPROPERTY()
	bool DeletedAfterSpawnActor;

	//@see ItemBase::m_IsUnique
	UPROPERTY()
	bool IsUnique;

	//this value should set manually as it should be cetaed at run time or load form other save files.
	//The csv file or other config files will not contain this value.
	UPROPERTY()
	double DurationTime;

	//@see ItemBase::m_ItemMaxStackNumber
	UPROPERTY()
	int ItemMaxStackNumber;

	//This value should be transient as it only be create at runtime or load from other save files.
	//This value can only be set mannuly, the csv file which the tablerow process will not contain this information
	FString ItemGUID;

	//this value should set manually as it should be cetaed at run time or load form other save files.
	//The csv file or other config files will not contain this value.
	double CreateTime;

	//this value should set manually as it should be cetaed at run time or load form other save files.
	//The csv file or other config files will not contain this value.
	int ItemNumber;



	/*
	* Convert and return a json Object string
	*/
	FString ToString() const 
	{
		return CreateJsonStringForAttributs();
	}

	/*
	* Callback function, it will be called after the UDataTable has processed the csv file.
	*/
	virtual void OnPostDataImport(const UDataTable* InDataTable, const FName InRowName, TArray<FString>& OutCollectedImportProblems) override
	{
		Super::OnPostDataImport(InDataTable, InRowName, OutCollectedImportProblems);

		iItemType.FirstLayer = ConventEnumerationStringToIntValue(ItemType.FirstLayer);
		iItemType.SecondLayer = ConventEnumerationStringToIntValue(ItemType.SecondLayer);
		iItemType.ThirdLayer = ConventEnumerationStringToIntValue(ItemType.ThirdLayer);
		iItemType.Fourthlayer = ConventEnumerationStringToIntValue(ItemType.Fourthlayer);
	}

	/*
	* Override by subclass to add its own variable to json string, this function should be map to DeSeializeJsonString
	*/
	virtual void GenerateJsonString(TSharedPtr<FJsonObject>& JsonObject) const {}

	/*
	* Override by subclass to deserialize Json string  to variables, this function should be map to GenerateJsonString
	*/
	virtual void DeSeializeJsonString(TSharedPtr<FJsonObject>& JsonObject) {}

	/*
	* Try to create one JsonString to contain the attributes which cannot be read from client.
	*
	* Mostly this function is called on server to prepare the data to transfer to client.
	*
	* @param attributsInfo	the attributes value that we will used to create one json value.
	*
	*/
	FString CreateJsonStringForAttributs() const
	{
		FString OutputString;
		TSharedRef< FCondensedJsonStringWriter > Writer = FCondensedJsonStringWriterFactory::Create(&OutputString);
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

		JsonObject->SetBoolField(FString(TEXT("Deleteable")), this->Deleteable);
		JsonObject->SetBoolField(FString(TEXT("CanBeSpawned")), this->CanBeSpawned);
		JsonObject->SetBoolField(FString(TEXT("Stackable")), this->Stackable);
		JsonObject->SetBoolField(FString(TEXT("DeletedAfterSpawnActor")), this->DeletedAfterSpawnActor);
		JsonObject->SetBoolField(FString(TEXT("IsUnique")), this->IsUnique);

		JsonObject->SetStringField(FString(TEXT("BindActorItemClassName")), this->BindActorItemClassName);
		JsonObject->SetStringField(FString(TEXT("ItemGUID")), this->ItemGUID);

		JsonObject->SetNumberField(FString(TEXT("DurationTime")), this->DurationTime);
		JsonObject->SetNumberField(FString(TEXT("CreateTime")), this->CreateTime);
		JsonObject->SetNumberField(FString(TEXT("ItemNumber")), this->ItemNumber);
		JsonObject->SetNumberField(FString(TEXT("ItemMaxStackNumber")), this->ItemMaxStackNumber);

		TSharedPtr<FJsonObject> DefaultPriceJsonObject = MakeShareable( new FJsonObject() );
		for (auto it : this->ItemDefaultPrice)
		{
			CHAR name[128];
			FMemory::Memset(name, 0x00);
			sprintf_s(name, "%d", it.Key.GetValue());
			DefaultPriceJsonObject->SetNumberField(FString(name), it.Value);
		}
		JsonObject->SetObjectField(FString(TEXT("ItemDefaultPrice")), DefaultPriceJsonObject);

		GenerateJsonString(JsonObject);

		check(FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer));

		DefaultPriceJsonObject.Reset();

		JsonObject.Reset();

		return OutputString;
	}

	FItemBaseInfo* DeSerializeJsonStringToAttributes(FString& JsonString)
	{
		TSharedRef< TJsonReader<> > Reader = TJsonReaderFactory<>::Create(JsonString);
		TSharedPtr<FJsonObject> JsonObject;

		check(FJsonSerializer::Deserialize(Reader, JsonObject));
		check(JsonObject.IsValid());

		if (JsonObject->HasField(FString(TEXT("Deleteable"))))
			Deleteable = JsonObject->GetBoolField(FString(TEXT("Deleteable")));
		if (JsonObject->HasField(FString(TEXT("CanBeSpawned"))))
			CanBeSpawned = JsonObject->GetBoolField(FString(TEXT("CanBeSpawned")));
		if (JsonObject->HasField(FString(TEXT("Stackable"))))
			Stackable = JsonObject->GetBoolField(FString(TEXT("Stackable")));
		if (JsonObject->HasField(FString(TEXT("DeletedAfterSpawnActor"))))
			DeletedAfterSpawnActor = JsonObject->GetBoolField(FString(TEXT("DeletedAfterSpawnActor")));
		if (JsonObject->HasField(FString(TEXT("IsUnique"))))
			IsUnique = JsonObject->GetBoolField(FString(TEXT("IsUnique")));

		JsonObject->TryGetStringField(FString(TEXT("BindActorItemClassName")), BindActorItemClassName);
		JsonObject->TryGetStringField(FString(TEXT("ItemGUID")), ItemGUID);
		JsonObject->TryGetNumberField(FString(TEXT("DurationTime")), DurationTime);
		JsonObject->TryGetNumberField(FString(TEXT("CreateTime")), CreateTime);
		JsonObject->TryGetNumberField(FString(TEXT("ItemNumber")), ItemNumber);
		JsonObject->TryGetNumberField(FString(TEXT("ItemMaxStackNumber")), ItemMaxStackNumber);

		const TSharedPtr<FJsonObject>* ItemDefaultPirceObject;
		JsonObject->TryGetObjectField(FString(TEXT("ItemDefalutPrice")), ItemDefaultPirceObject);

		check(ItemDefaultPirceObject->IsValid());

		for (int i = 0; i < EItemPriceType::EItemPriceType_Max; i++)
		{
			char name[128];
			FMemory::Memset(name, 0x00);
			sprintf_s(name, "%d", i);
			int price = 0;
			if (ItemDefaultPirceObject->Get()->TryGetNumberField(FString(name), price))
				ItemDefaultPrice.Add(EItemPriceType(i), price);
		}

		DeSeializeJsonString(JsonObject);

		return this;
	}

private:

	INT FItemBaseInfo::ConventEnumerationStringToIntValue(FString enumeration)
	{
		SEARCHINENUMERATION(EINVENTROYTYPE, enumeration)
		SEARCHINENUMERATION(ECONSUMABLETYPE, enumeration)
		SEARCHINENUMERATION(ECAPSULETYPE, enumeration)
		SEARCHINENUMERATION(EUNCONSUMABLETYPE, enumeration)
		SEARCHINENUMERATION(EWEAPONTYPE, enumeration)
		SEARCHINENUMERATION(EGUNTYPE, enumeration)
		SEARCHINENUMERATION(EACCESSORYTYPE, enumeration)
		return -1;
	}
};
