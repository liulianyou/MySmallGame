/*
* Author:	Kayak_Liulianyou
* Time:		2017/6/6
* Purpose:	All the definitions include marco, struct which will be used by other game mode session should be declared here.
			This file will only used to communicate between other game mode session and UI,the declarations which will be only used in the UI internally should be writen in UIBase.h file
*/

#pragma once

//Engine Core Head:Contained all marco that used in UObject
#include "UObject/ObjectMacros.h"
//Engine Core Head:Used to store json or csv file to table struct
#include "Engine/DataTable.h"

//Automatically generated head file
#include "UIInterfaceDefination.generated.h"

/*
* This enumeration will contains all the UI our game contained.
* Each value will combined with EUIType_ with the UI's name.
*
* Notice: When you add new UI to our game you should add new enumeration in it, add use {@Function CreateUI} in UUIInterface.h to create new UI.
*/
UENUM(BlueprintType, Meta = (Bitflags))
enum EUIType
{
	EUIType_LogIn			UMETA( DisplayName="Login" ),									//Represent for the Login UI

	EUUIType_MiniMap		UMETA( DisplayName="MiniMap" ),									//Present for the minimap 

	EUIType_LevelMap		UMETA( DisplayName="LevelMap" ),								//Present for level Map which shows all the information of current level.

	EUIType_Teammate		UMETA(	DisplayName="Teammate" ),								//Present for UI to show the team's information

	EUIType_Friend			UMETA( DisplayName="Friend" ),									//Show all the friend's information of current account.

	EUIType_AvaterSelect	UMETA( DisplayName="AvaterSelect" ),							//Show all the avaters in one account.

	EUIType_AvaterCreate	UMETA( DisplayName="AvaterCreate" ),							//Show the information of how to create one avater

	EUIType_Shop			UMETA( DisplayName="Shop" ),									//Show shop's information 

	EUIType_HUD_Widget		UMETA(DisplayName = "HUDTest"),									//HUD for test

	EUIType_MaxNum			UMETA( DisplayName="The Max number of UI in our game" )			//Reserved for calculate total UI's number in our game
};			

/*The data struct to store the information of one icon image*/
USTRUCT(BlueprintType)
struct FIconDetails : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FString Path;

	UPROPERTY(EditAnywhere, meta = (ClampMin = 1))
	float U;

	UPROPERTY(EditAnywhere, meta = (ClampMin = 1))
	float V;

	UPROPERTY(EditAnywhere, meta = (ClampMin = 1))
	float W;

	UPROPERTY(EditAnywhere, meta = (ClampMin = 1))
	float H;
};
																								
