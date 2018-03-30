/*
* Author:		Kayak_Liulianyou 
* Time:			2017/6/7
* Purpose:		This file will arrange the login UI element.
*				This file is just used to control the data that map to each elements in this widget and the logic relationship between them.
*				It will not set the location size of each elements as these attributes has been set when this widget is created.
*/

#pragma once

//Local include
#include "UIBase.h"

//Automatically generated head
#include "UILogIn.generated.h"

UCLASS(Config = UI)
class KAYAKGAME_API UUILogIn :public UUIBase
{
public:
	GENERATED_UCLASS_BODY()

	//Override the function in the base class
	virtual void InitializeLocalLogic();
	

protected:

	UFUNCTION()
	void ClickStartGameButton();

	UFUNCTION()
	void AnimationStart(const UWidgetAnimation* animation);

private:
	//UI Elements:
	UButton* m_StartGameButton;
	UButton* m_OptionButton;
	UButton* m_EndGameButton;
};