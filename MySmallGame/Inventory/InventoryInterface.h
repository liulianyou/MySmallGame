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


UCLASS(BlueprintType)
class KAYAKGAME_API InventoryInterface : public UObject
{

public:
	
	static KAYAGAME_API const UDataTable* GetItemSimpleInfoDataType() {};




};

