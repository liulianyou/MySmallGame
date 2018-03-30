//Local include
#include "UIInterface.h"
#include "./Public/UIManage.h"

UUserWidget* UUIInterface::CreateUI( EUIType UITypeName, UWorld* world)
{
	return UUIManage::GetInstance()->CreateUI( UITypeName );
}

bool UUIInterface::CloseUI(UUserWidget* targetWidget, bool needUnload)
{
	return UUIManage::GetInstance()->CloseUI(targetWidget, needUnload);
}

bool UUIInterface::ShowUI(UUserWidget* targetWidget)
{
	return UUIManage::GetInstance()->ShowUI(targetWidget);
}

void UUIInterface::CreateUIManageInstance( )
{
	UUIManage::CreateInstance();
}

UUIBase* UUIInterface::GetBindClass(UUserWidget* targetWidget)
{
	return UUIManage::GetInstance()->GetBindClass(targetWidget);
}

