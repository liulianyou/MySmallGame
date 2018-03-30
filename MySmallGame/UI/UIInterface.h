/*
* Author:	Kayak_Liulianyou;
* Time:		2017/6/5 - 
* Purpose:	
*			This file will be used as interface for other gameplay mode such as worldInfo, AI or any other one which the designers don't care about the details of the UI implemation.
*			
*			This class will be singleton in our game.
*/

#pragma once

//Engine Core Include
#include "UObject/ObjectMacros.h"
#include "Blueprint/UserWidget.h"

//Local Include
#include "Public/UIInterfaceDefination.h"

//Automatically generated head file
#include "UIInterface.generated.h"

class UUIManage;
class UUIBase;

UCLASS()
class KAYAKGAME_API UUIInterface :public UObject
{
public:

	GENERATED_BODY()
	
	/*
	* Interface to create UI by the enumeration EUIType.
	*
	* @param UITypeName		The specific UI that need to create.
	* @param world			The owner of this UI.
	* @return the final UI widget istance which is created, Null means create faild.
	*/
	UFUNCTION(BlueprintCallable, Category = "Kayak|UI|Interface", meta=(WorldContext = "WorldContextObject"))
	static UUserWidget* CreateUI( EUIType UITypeName, UWorld* world = nullptr);

	/*
	* Interface to show one specific UI to the screen;
	* Before you use this function you should make sure the target widget have been opened and not realase from memory.
	* Or you maybe instead it with CreateUI function.
	*
	* @param	targetWidget the specific widget that should be showed in the screen.
	* @return	true means this action is successed, 
	*			false means the specific widget is not exsit in current scrren.	Plase make sure weather you have realse it or have not open it yet.				  
	*/
	UFUNCTION( BlueprintCallable, Category = "Kayak|UI|Interface" )
	static bool ShowUI(UUserWidget* targetWidget);


	/*
	* Interface to Close UI through the specific widget;
	*
	* @param targetWidget the target widget that we need to close.
	* @param needUnload true means we will unload this widget form memory, false we will just set it visible to be false. and remove its focus.
	* @return ture means action success, false means failed
	*/
	UFUNCTION(BlueprintCallable, Category = "Kayak|UI|Interface")
	static bool CloseUI(UUserWidget* targetWidget, bool needUnload = false);

	/*
	* Get the native class which bind with the target widget;
	* 
	* @param targetWidget the target widget which we try to get its bind class
	*/
	UFUNCTION(BlueprintCallable, Category = "Kayak|UI|Interface")
	static UUIBase* GetBindClass(UUserWidget* targetWidget);

	UFUNCTION(BlueprintCallable, Category = "Kayak|UI|Interface")
	static void CreateUIManageInstance();
	
};

