/*
* Author:	Liulianyou
* Time:		2019/2/6
* Purpose:	This class i a class to manager all the game UI, just like one factory.
*/

#pragma once

#include "CoreMinimal.h"
#include "Serialization/JsonSerializerMacros.h"

#include "UIManager.generated.h"

class AHUD;
class UUserWidget;
class UUIBase;

UENUM()
enum struct EUIGroup : uint8
{
	EUIGroup_Main		UMETA( DisplayName="Main UI" ),
	EUIGroup_Max		UMETA( DisplayName="Max Count" )
};

UENUM()
enum struct EUIType : uint8
{
	EUIType_Login		UMETA( DisplayName="Login"),
	EUIType_Max			UMETA( DisplayName="Max Count" )
};

//The type to open a new UI
UMETA()
enum struct EOpenUIStyle : uint8
{
	//When we open UI we need to create new UWidget and new correspond native class
	EOpenUIStyle_CreateWidgetAndNativeClass	= 1<<0	UMETA( DisplayName="Create Widget & Native Class" ),
	//When we open UI we only need to create new UWidget
	EOpenUIStyle_OnlyCreateWidget			= 1<<1	UMETA( DisplayName="Only Create Widget" ),
	//When we open UI we only need to create new native class
	EOpenUIStyle_OnlyCreateNativeClass		= 1<<2	UMETA( DisplayName="Only Create Native Class" ),
	EOpenUIStyle_Max						UMETA( DisplayName="Max Count" )
};

UENUM()
enum struct EUILayer : uint8
{
	EUILayer_Bottom				UMETA( DisplayName="Bottom" ),
	EUILayer_GameMessage		UMETA( DisplayName="Game Message" ),
	EUILayer_DebugMessage		UMETA( DisplayName="Debug Message" ),
	EUILayer_Top				UMETA( DisplayName="TOP" ),
	EUILayer_Max				UMETA( DisplayName="Max Count" )
};

//Struct stands for the map between group and UI types
class FUIGroupMap : public FJsonSerializable
{
public:
	FUIGroupMap() {}
	~FUIGroupMap() {}
public:
	//Key value for the UIGroup which actual type is EUIGroup
	int32 Group;
	//Value for the UIs which is belong to the Group, this Actual type is EUIType
	TArray<int32> UITypes;

	bool operator==(const EUIGroup& Group)
	{
		if (this->Group == int32(Group)) return true;
		else return false;
	}

public:
	//FJsonSerializable
	BEGIN_JSON_SERIALIZER
	JSON_SERIALIZE("Group", Group);
	JSON_SERIALIZE_ARRAY("UITypes", UITypes);
	END_JSON_SERIALIZER

};

/*
* Struct stands for the map between UITYpe and UI name
* One type refer to the name and the name should be the widget's name in the UE4 asset
*/
class FUITypeMap :public FJsonSerializable
{
public: 
	FUITypeMap() {}
	~FUITypeMap() {}
public:
	//Key Value for the UIType which actual type is EUITYpe
	int32 UIType;
	//The base name of the widget we created. we will combine it with
	FString UIBaseName;
	//The path of the UI widget asset in the UE4 browser content
	FString UIWidgetAssetPath;
	//The path of native class path which will bind with the widget asset
	FString UINativeClassPath;

	bool operator==(const EUIType& UIType)
	{
		if (this->UIType == int32(UIType)) return true;
		else return false;
	}
public:
	//FJsonSerializable
	BEGIN_JSON_SERIALIZER
	JSON_SERIALIZE("UIType", UIType);
	JSON_SERIALIZE("UIWidgetAssetPath", UIWidgetAssetPath);
	JSON_SERIALIZE("UINativeClassPath", UINativeClassPath);
	END_JSON_SERIALIZER
};

/*
* The operation when we close the UI,
* If CanDeleteWidget && CanDeleteNativeClass is true means we need to delete the UUIWidget instance in the UI Pool
*/
USTRUCT(Blueprintable)
struct FCLoseUIParameter
{
	GENERATED_USTRUCT_BODY()

	FCloseUIParamater() :
		CanDeleteNativeClass(true),
		CanDleteWidget(true),
		ResetWidget(true),
		RestNativeClass(true)
	{}

	/*
	* Weather we should delete the instance of the widget when we close the UI
	* If this value is false we swill just hide this widget, and disable all its interaction.
	*/
	bool CanDeleteWidget;
	/*
	* Weather we should delete the instance of the native class when we close the UI
	*/
	bool CanDeleteNativeClass;
	/*
	* Weather we should reset the widget instance to make all its elements to the original state
	* This value only work when the CanDeleteWidget is false
	*/
	bool ResetWidget;
	/*
	* Weather we should reset the native class when we close the UI
	* This value on work when the CanDeleteWidget is false
	*/
	bool ResetNativeClass;

	static FCLoseUIParameter DefaultParameter;
};

USTRUCT(Blueprintable)
struct FOpenUIParameter
{
	GENERATED_USRUCT_BODY()

	FOpenUIParameter():
		OpenUIStyle(EOenUIStyle_CreateWidgetAndNativeClass),
		UILayer(EUILayer_Bottom),
		UIGroup(EUIGroup_Main),
		ForceAddToUIPool(false),
		AutoGeneratedName(true),
		FString OverrideName(TEXT("New Instance"))
	{}

	//The Style to create new UI add to the UI pool
	EOpenUIStyle OpenUIStyle;

	//The layer that this UI Stay
	EUILayer UILayer;

	//The target group which the new UI want to stay.
	EUIGroup UIGroup;
	/*
	* weather the new UUIWidget need to force adding it to the pool.
	* False means we will not create new UUIIwidget Instance if the old instance with the same UUIType has been exist in the UI Pool,
	*		And just update it's UILayer(will change tis actual layer), group.
	*		But if there is no instance in the UI pool we will create the new UUIWidget to pool.
	* True means we will crate new UUIWidget to UI pool
	*/
	bool ForceAddToUIPool;

	//;Check weather we need to generate new Name automatically for the UWidget instance and the NativeClass
	bool AutoGeneratedName;

	//Specify the name for the Widget and Native Class, it only work the AutoGeneratedName is false
	FString OverrideName;

	static FOpenUIParameter DefaultParameter;
};

/*
* The UI widget of each value in the UIManager.
* The member of the UIGroup and UIType is different from the
*/
UCLASS()
class UUIWidget :public UObject
{
	GENERATED_BODY()
	UUIWidget() {}

public:
	//Stored the actual group which the target UIElement belongs to.
	EUIGroup UIGroup;
	//The actual UITYpe which the target UElement is.
	EUIType UIType;
	//The layer that the urrent widget stay.
	EUILayer UILayer;
	//The Element of the UI
	TSharedPtr<UUserWidget> UIElement;
	//The instance of native class
	TSharedPtr<UUIBase> UINativeClassInstance;
public:
	void Initialize();
};

UCLASS()
class UUIManage : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	//The owner of HUD which will hold the instance of this class
	AHUD* HUDOwner;
public:
	static TArray<FUIGroupMap>& GetUIGroupMap();
	static TArray<FUITypeMap>& GetUITypeMap();

private:
	static FString GetUIGroupJsonData();
	static void SetUIGroupMap(FString GroupMap);

	static FString GetUITypeJsonData();
	static void SetUITypeMap(FString UITypeMapString);

public:
	//Open all the UI widgets which belong to the target group
	UFUNCTION(BlueprintCallable, Category = UI)
	bool OpenGroupUI(EUIGroup UIGroup, TArray<UUIWidget*>& OutWidgets);
	UFUNCTION(BlurprintCallable, Category = UI)
	bool CloseGroupUI(EUIGroup UIGroup, const FCLoseUIParameter& Parameter);
	UFUNCTION(BlurprintCallable, Category = UI)
	UUIWidget* OpenUI(EUIType UIType, const FOpenUIParameter& Parameter);
	UFUNCTION(BlurprintCallable, Category = UI)
	void CloseUIByWidget(UUIWidget* Widget);
	UFUNCTION(BlurprintCallable, Category = UI)
	void CloseUIByUIType(EUIType UIType);
protected:

	UUIWidget* AddNewUIWidgetToUIPool(EUIType UIType, int index, const FOpenUIParameter& Parameter);

private:
	//Hold all UIs which has been opened once and its resource have not been released
	TArray<UUIWidget*> TotalUIPool;

	/*
	* Config map of all UI, the value TArray<FString> is the array of the UI name.
	* The UI type maybe not correspond to the target UIGroup in the running time,
	* as we may add one UI to another UIGroup.
	* This value is just used to offer one soulution for the UItype and UIGroup
	* such as we may use OpenGroupUI to Open one Category of UI.
	*/
	static TArray<FUIGroupMap> UIGroupMap;

	//Config map for the EUITYpe and tharget actual widget's name
	static TArray<FUITypeMap> UITypeMap;
};



