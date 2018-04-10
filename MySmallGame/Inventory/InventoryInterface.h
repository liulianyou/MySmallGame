#pragma once

/*
* Author:	Kayak_Liulianyou
* Time:		2018/3/19
* Purpose:	
			This class will hold all the interface for other module or dll to hand the Inventory
*/

//Engine Core Head:Contained all marco that used in UObject
#include "UObject/ObjectMacros.h"

//Local include
#include "Public/InventoryDefination.h"

#include "InventoryInterface.generated.h"


UCLASS(BlueprintType)
class KAYAKGAME_API UInventoryInterface : public UObject
{

public:

	GENERATED_UCLASS_BODY()
	
	//UFUNCTION()
	//const UDataTable* GetItemSimpleInfoDataType() { return nullptr; };




};

