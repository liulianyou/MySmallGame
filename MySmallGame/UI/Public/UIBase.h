/*
* Author:		Kayak_Liulianyou
* Time:			2017/6/8
* Purpose:		UIBase is the base class of all UI in our game.
*				In this class we will add the common functions that will be called multiplies to it.
*				The SubClass which derived form UIBase will be used to generate and set the Data that we need to displayed to the specific UI
*				and the SubClass will also controlled the relationship between the each elements in UI.
*				I just want the UMG to set the layout, animation, or widgetStytle of each elements, the logic relationship and data setting should put in C++ file not in BluePrint,
*				as the Blueprint is hard to debug when some bugs occur in the future.
*/

#pragma once

//Engine Core Head:Contained all marco that used in UObject
#include "UObject/ObjectMacros.h"
//UMG Core Head: This will contained all elements that we will used in UI
#include "UMG.h"

#include "UI/UIManager.h"
//Automatically generated head file
#include "UIBase.generated.h"

class UUserWidget;
class APlayerController;
class APawn;

UCLASS(Config = UI)
class KAYAKGAME_API UUIBase : public UObject
{
public:
	GENERATED_UCLASS_BODY()

	/*
	* When new UI Created we will use this function to initialize local logic, 
	* such as generate data form other GameMode, Map the UI elements to local memeber values.
	* This function should be override by derived class
	*/
	virtual void InitializeLocalLogic() {};

	void Initialize( UUIWidget* Owner );

	UUserWidget* GetTargetUserWidget();
	APlayerController* GetOwningPlayerController();
	APawn* GetOwningPawn();
	UUIManage* GetOwningUIManager();
	

protected:

	/**
	* This function will used to map the UIElement to the local member so that we can access it form c++ code.
	* @param path the path of target UI element. this path should relative to the root node. and each hierarchy should be broken up by '.'
	*		 Just like "CanvasPanel_0.StartButton", which CanvasPanel_0 is stand for the root panel of this user widget and StartButton is one child of it.
	*		 the hierarchy shows like below:
	*		 _______________________
	*		 |CanvasPanel_0			|
	*		 |	________________	|
	*		 |  |StartButton    |	|
	*		 |  |OptionButton   |	|
	*		 |  |_______________|   |
	*		 |______________________|
	*	@return the target value which will store the element
	*/
	template<typename type>
	type* UUIBase::MapUIElementToLocalVariable(const FString path)
	{
		UWidget* tempWidget = nullptr;

		TArray<FString> herichyValue;
		if (!parseDotString(herichyValue, path)) return (dynamic_cast<type*>(tempWidget));

		for (int i = 0; i < herichyValue.Num(); i++)
		{
			tempWidget = GetImmediateUIElementByName(tempWidget, herichyValue[i]);
			if (tempWidget == nullptr)
			{
				//FMessageLog("KayakUIError").Error("There is no widget which name is %s in the full path: %s", *herichyValue[i], *path);
				break;
			}
		}

		return ((dynamic_cast<type*>(tempWidget)));
	}

private:

	/*
	* Breaks up path string, so that we can find the final target UI Element.
	*/
	bool parseDotString( TArray<FString>& herichyValue, const FString path );

	/*
	* Get the UI element by its name, this range to find is the immediate children.
	* @param parentWidget the target widget which should contain the UI element which name is UIName
	* @param UIName the target element's name that we want to find.this name is the displayed label value not the class's name,
	*		 Please make sure this name is unique in one layer or this will not get the right widget
	*/
	UWidget* GetImmediateUIElementByName(UWidget* parentWidget, const FString UIName);

private:
	UUIWidget* WidgetOwner;
};
