#include "UIManager.h"

TArray<FUIGroupMap> UUIManage::UIGRoupMap = TArray<FUIGroupMap>();
TArray<FUIGroupMap> UUIManage::UITypeMap = TArray<FUITypeMap>();

const FCloseUIParameter FCloseUIParameter::DefaultParameter;
const FOpenUIParameter FOpenUIParameter::DefaultParameter;

UUIManage::UUIManager(const FObjectInitializer& ObjectIntializer):
	Super(ObjectIntializer)
{}



