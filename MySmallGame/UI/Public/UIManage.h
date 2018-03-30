/*
* Author: Kayak_MarsLiulianyou
* Time: 2017/6/6 -
* Purpose: All the management of the UI in our game will be manipulated in this class.
*		   You can treat this class to be the factory to manage all the UI,.
*		   If you add new UI native class you should register the target native calss in {@Function RegisterUINativeClass}
*		   And add new instance creation in {@Function CreateNativeClassObject}
*		   This class is used for singleton instane.
*		   Notice: many function you can see is the same in UUIInterface, but I don't make UUIManage to inherit form UUIInterface.
*				   The reason is UUIManage is aimed at the UI, and the UUIInterface is aimed at the designer who donn't care about how this UI is implemented.
*/

#pragma once

//Engine Core Include
#include "UObject/ObjectMacros.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"

//Local Include
#include "UIInterfaceDefination.h"

class UUIBase;

class KAYAKGAME_API UUIManage 
{
public:

	/*
	* Used to create UI by the enumeration EUIType.
	*
	* @param UITypeName		The specific UI that need to create.
	*
	* @return the final UI widget instance which is created, Null means create failed. Default value is true
	*/
	UUserWidget* CreateUI(EUIType UITypeName, UWorld* world = GWorld);

	/*
	* Interface to show one specific UI to the screen;
	*
	* @param	targetWidget the specific widget that should be showed in the screen.
	* @return	true means this action is successfull,
	*			false means the specific widget is not exist in current screen.	Please make sure weather you have release it or have not open it yet.
	*/
	bool ShowUI(UUserWidget* targetWidget);

	/*
	* Used to Close UI through the specific widget;
	*
	* @param targetWidget the target widget that we need to close.
	* @param needUnload true means we will unload this widget form memory, false we will just set it visible to be false. and remove its focus.
	* @return ture means action success, false means failed;Bynow the default value is false
	*/
	bool CloseUI(UUserWidget* targetWidget, bool needUnload = false);

	/*
	* Get the native class which bind with the target widget;
	*
	* @param targetWidget the target widget which we try to get its bind class
	*/
	UUIBase* GetBindClass(UUserWidget* targetWidget);



protected:

private:

	/*
	* The data that each type of UI referred to.
	*/
	struct UIBindData
	{
		UIBindData(FString _UISourceName, FString _NativeUIClassName)
		{
			UISourceName = _UISourceName;
			NativeUIClassName = _NativeUIClassName;
		}

		//The actual art source of UI which is created through UMG tool by artiest
		FString UISourceName;

		// The the target name of native class which name is usually not contained prefix 'U'.
		FString NativeUIClassName;
	};

	/*
	* Initialize the local logic such as local memeber value;
	*/
	void Initialize();

	/*
	* Try to crate native class object that will bind with the UserWidget
	*/
	UUIBase* CreateNativeClassObject(EUIType type, UUserWidget* widget );

	/*
	* Register the native calss and the UI Type date;
	*/
	void RegisterUINativeClass();

private:
	//All the pending UI that we need to open in the further.
	TMap<UUIBase*, UUserWidget*> m_PendingUserWidget;

	//All opened UI Instance will be restored in this member
	TMap<UUIBase*,UUserWidget*> m_OpenedUserWidget;

	//The map between the UserWidget class and the enumeration. We can use this member to create the specific UI instance
	TMap<EUIType, UIBindData> m_UserWidgetMap;


#pragma region SingletonSupport
public:

	//Create instance; This function will be called as our gamemode is initialized
	static void CreateInstance();

	//Get instance; the UI designer will use this function to get access to manipuate UI
	static UUIManage* GetInstance();

	//Before we exit our game we should release it.
	static void DestoryInstance();

protected:
private:
	UUIManage();
	~UUIManage();

	static UUIManage* s_mInstance;
#pragma endregion SingletonSuppot
};