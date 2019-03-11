/*
* Author:	Liulianyou
* Time:		2019/2/6
* Purpose:	This class i a class to manager all the game UI, just like one factory.
*/

#pragma once

#include "CoreMinimal.h"

#include "UserWidget.h"

#include "UIManager.generated.h"

class AHUD;
class UUserWidget;
class UUIBase;

UENUM(Blueprintable)
enum struct EUIGroup : uint8
{
	EUIGroup_Main		UMETA( DisplayName="Main UI" ),
	EUIGroup_Max		UMETA( DisplayName="Max Count" )
};

/*
* As the BP only support the 8 bit enumeration . this will cause the final UIType is exceed the range of EMainUIType
* I add another hierarchy which is higher than EMainUItype to make the OpenUI/OpenGroup... will work forever
* And Only the UI types in the EMainUIType will add to view port's slot.
*/
UENUM(Blueprintable)
enum struct EUICategoryType :uint8
{
	EUICategory_Main			UMETA(DisplayName="Main Category"),
	EUICategory_Component		UMETA(DIsplayName="Component"),
	EUICategory_Max				UMETA(DisplayName="Max Count)
};

/*
* Enumeration for the UI component.
* UI component's hierarchy is higher than widget and less than UI.
* As some UMG component will create widget automatically in the internal usage to support some function such as list view,
* I want one enumeration to identify the customize component to make it easier to maintain it.
*/
UENUM(Blueprintable)
enum class EUIComponentType : uint8
{
	EUICOmponentTYpe_ReplayViewListEntry	UMETA(DisplayName ="Replay View List Entry"),
	EUICOmponentTYpe_Max					UMETA(DisplayName="Max Count)
};

/*
* Enumeration used to stand for the ENTIRUE UI which is category of the widget elements.
* many widget elements will be combined to been on UI, and the local native class will manipulate the whole category of widgets
*/
UENUM(Blueprintable)
enum struct EMainUIType : uint8
{
	EUIType_Login		UMETA( DisplayName="Login"),
	EUIType_Max			UMETA( DisplayName="Max Count" )
};

//The type to open a new UI
UMETA(Blueprintable)
enum struct EOpenUIStyle : uint8
{
	//When we open UI we need to create new UWidget and new correspond native class
	EOpenUIStyle_CreateWidgetAndNativeClass	= 1<<0	UMETA( DisplayName="Create Widget & Native Class" ),
	//When we open UI we only need to create new UWidget
	EOpenUIStyle_OnlyCreateWidget			= 1<<1	UMETA( DisplayName="Only Create Widget" ),
	//When we open UI we only need to create new native class
	EOpenUIStyle_OnlyCreateNativeClass		= 1<<2	UMETA( DisplayName="Only Create Native Class" ),
	EOpenUIStyle_Max								UMETA( DisplayName="Max Count" )
};

UENUM(Blueprintable)
enum struct EUILayer : uint8
{
	EUILayer_Bottom				UMETA( DisplayName="Bottom" ),
	EUILayer_GameMessage		UMETA( DisplayName="Game Message" ),
	EUILayer_DebugMessage		UMETA( DisplayName="Debug Message" ),
	EUILayer_Top				UMETA( DisplayName="TOP" ),
	EUILayer_Max				UMETA( DisplayName="Max Count" )
};

USTRUCT(Blueprintable)
struct FUIType
{
	GENERATED_STRUCT_BODY()
public:
	FUIType() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, CategoryUI = UI)
	EUICategoryType UICategoryType;

	/*
	*
	* You can treat this value to be secondlly type to specify the UI,
	* Such as when the UIcategroy type is EUICategroy_Main, UIType's value is one of the EMainUIType,
	* when the UICategroy type is EUICategroy_Component is, UIType's value is one of the EUIComponentType
	* I want to use union struct to hold this value but blueprint doesn't support.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, CategoryUI = UI)
	uint8 UIType;

	bool operator==(const FUIType& Other) const
	{
		if (UICategoryType == Other.UICategoryType && UIType == Other.UIType)
			return true;
		else
			return false;
	}

	bool operator!=(const FUIType& Other) const
	{
		if (UICategoryType != Other.UICatetgoryType ||
			UIType != Other.UIType)
			return true;
		else
			return false;
	}

	bool operator<(const FUIType& Other) const
	{
		if (UICategoryType != Other.UICategoryType)
			return UICategroyType < Other.UICategroyType;
		else if (UIType != Other.UIType)
			return UIType < Other.UIType;
		else return false;
	}
};

//Struct stands for the map between group and UI types
USTRUCT(Blueprintable)
class FUIGroupMap : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FUIGroupMap() {}
	virtual ~FUIGroupMap() {}
public:
	//Key value for the UIGroup
	UPROPERTY(EditAnywhere, BlueprintReadWrite, CategoryUI = UI)
	EUIGroup Group;
	//Value for the UIs which is belong to the Group
	UPROPERTY(EditAnywhere, BlueprintReadWrite, CategoryUI = UI)
	TArray<FUIType> UITypes;

};

/*
* Struct stands for the map between UITYpe and UI name
* I will through the UIType to get the UI widget and UI native class
*/
USTRUCT(Blueprintable)
class FUITypeMap : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public: 
	FUITypeMap() {}
	virtual ~FUITypeMap() {}
public:
	//Key Value for the UIType which actual type is EUITYpe
	UPROPERTY(EditAnywhere, BlueprintReadWrite, CategoryUI = UI)
	FUIType UIType;
	//The base name of the widget we created. we will combine it with
	UPROPERTY(EditAnywhere, BlueprintReadWrite, CategoryUI = UI)
	FString UIBaseName;
	//The path of the UI widget asset in the UE4 browser content
	UPROPERTY(EditAnywhere, BlueprintReadWrite, CategoryUI = UI)
	FString UIWidgetAssetPath;
	//The path of native class path which will bind with the widget asset
	UPROPERTY(EditAnywhere, BlueprintReadWrite, CategoryUI = UI)
	FString UINativeClassPath;

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, CategoryUI = UI)
	bool CanDeleteWidget;
	/*
	* Weather we should delete the instance of the native class when we close the UI
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, CategoryUI = UI)
	bool CanDeleteNativeClass;
	/*
	* Weather we should reset the widget instance to make all its elements to the original state
	* This value only work when the CanDeleteWidget is false
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, CategoryUI = UI)
	bool ResetWidget;
	/*
	* Weather we should reset the native class when we close the UI
	* This value on work when the CanDeleteWidget is false
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, CategoryUI = UI)
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, CategoryUI = UI)
	EOpenUIStyle OpenUIStyle;

	//When the OpenUIStyle is EOpenUIStyle_OnlyCreateWidget means we will use the user widget which is pass from others
	UPROPERTY(EditAnywhere, BlueprintReadWrite, CategoryUI = UI)
	UUserWidget* UIElement;

	//When the OpenUIStyle is EOpenStyle_OnlyCreateNativeClass means we will use the native class which is pass from others.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, CategoryUI = UI)
	UUIBase* UINativeClass;

	//The layer that this UI Stay
	UPROPERTY(EditAnywhere, BlueprintReadWrite, CategoryUI = UI)
	EUILayer UILayer;

	//The target group which the new UI want to stay.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, CategoryUI = UI)
	EUIGroup UIGroup;
	/*
	* weather the new UUIWidget need to force adding it to the pool.
	* False means we will not create new UUIIwidget Instance if the old instance with the same UUIType has been exist in the UI Pool,
	*		And just update it's UILayer(will change tis actual layer), group.
	*		But if there is no instance in the UI pool we will create the new UUIWidget to pool.
	* True means we will crate new UUIWidget to UI pool
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, CategoryUI = UI)
	bool ForceAddToUIPool;

	//;Check weather we need to generate new Name automatically for the UWidget instance and the NativeClass
	UPROPERTY(EditAnywhere, BlueprintReadWrite, CategoryUI = UI)
	bool AutoGeneratedName;

	//Specify the name for the Widget and Native Class, it only work the AutoGeneratedName is false
	UPROPERTY(EditAnywhere, BlueprintReadWrite, CategoryUI = UI)
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, CategoryUI = UI)
	EUIGroup UIGroup;
	//The actual UITYpe which the target UElement is.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, CategoryUI = UI)
	FUIType UIType;
	//The layer that the current widget stay.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, CategoryUI = UI)
	EUILayer UILayer;
	//The Element of the UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, CategoryUI = UI)
	UUserWidget* UIElement;
	//The instance of native class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, CategoryUI = UI)
	UUIBase* UINativeClassInstance;

	//External user data which is assigned from creator
	UObject* UserData;

	bool operator<(const UUIWidget& OtherWidget) const {
		if (UILayer != OtherWidget.UILayer)
			return UILayer < OtherWidget.UILayer;
		else if (UIGroup != OtherWidget.UIGroup)
			return UIGroup < OtherWidget.UIGroup;
		else if (UIType != OtherWidget.UIType)
			return UIType < OtherWidget.UIType;
		else return false;
	}

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
	bool OpenGroupUI(EUIGroup UIGroup,EUILayer UILayer, TArray<UUIWidget*>& OutWidgets);
	UFUNCTION(BlurprintCallable, Category = UI)
	bool CloseGroupUI(EUIGroup UIGroup, EUILayer UILayer=EUILayer::EUILayer_Max);
	UFUNCTION(BlurprintCallable, Category = UI)
	UUIWidget* OpenUI(FUIType UIType, const FOpenUIParameter& Parameter);
	UFUNCTION(BlurprintCallable, Category = UI)
	void CloseUIByWidget(UUIWidget* Widget, const FCLoseUIParameter& Parameter);
	UFUNCTION(BlurprintCallable, Category = UI)
	void CloseUIByUIType(FUIType UIType, const FCLoseUIParameter& Parameter);
protected:
	/*
	* Create new UUIWidget and add it to the UIPool
	* @param UIType					the type of UI that will add to UI pool
	* @param NameExtensionIndex		the index value for the suffix of the new instance's name
	* @param Parameter				the config parameter to open one new UI
	*/
	UUIWidget* AddNewUIWidgetToUIPool(EUIType UIType, int index, const FOpenUIParameter& Parameter);

	bool InitializeUITypeMap();
	bool InitializeUIGroupMap();

private:

	//Quick access to the UIGroupMap and UITypeMap data.
	TArray<FUIGroupMap*>	UIGroupMapArray;
	TArray<FUITypeMap*>		UITypeMapArray;

private:
	//Hold all UIs which has been opened once and its resource have not been released
	UPROPERTY(Transient)
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



