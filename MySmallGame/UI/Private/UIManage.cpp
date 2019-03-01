//Local include
#include "../Public/UIManage.h"

//System include
#include <stdio.h>

//Engine Header
#include "Engine/Engine.h"
#include "Engine/Blueprint.h"

//Include the UI Class head
#include "../Public/UIBase.h"
#include "../Public/UILogIn.h"

#define GetUserWidgetPath( x  ) FString("/Game/Interaction/HUD/") + FString( x )

#pragma region SingletonSupport

UUIManage* UUIManage::s_mInstance = nullptr;

UUIManage::UUIManage()
{
	Initialize();
}

UUIManage::~UUIManage()
{}

void UUIManage::CreateInstance()
{
	if (s_mInstance  == nullptr)
	{
		s_mInstance = new UUIManage();
	}
	else if (GEngine->IsEditor())
	{
		s_mInstance->Initialize();
	}
}

UUIManage* UUIManage::GetInstance()
{
	return s_mInstance;
}

void UUIManage::DestoryInstance()
{
	if (s_mInstance)
	{
		delete s_mInstance;
		s_mInstance = nullptr;
	}
}

#pragma endregion SingletonSuppot

UUserWidget* UUIManage::CreateUI( EUIType UIType, UWorld* world  )
{
	UUserWidget* result = nullptr;
	UBlueprint* UIWidgetBlueprint = nullptr;
	UIBindData* UIData = m_UserWidgetMap.Find( UIType );

	FString UIWidgetBlueprintPath = GetUserWidgetPath( UIData->UISourceName );

	UIWidgetBlueprint = LoadObject<UBlueprint>(NULL, *UIWidgetBlueprintPath, NULL, LOAD_None, NULL);

	result = CreateWidget<UUserWidget>(world == nullptr?GWorld : world, UIWidgetBlueprint->GeneratedClass);

	UUIBase* bindClassInstace = CreateNativeClassObject(UIType, result);

	m_PendingUserWidget.Add(bindClassInstace, result);

	return result;
}

bool UUIManage::ShowUI(UUserWidget* targetWidget)
{
	bool result = false;

	if (targetWidget == nullptr) return result;

	result = true;

	targetWidget->AddToViewport();

	for (auto& it : m_PendingUserWidget)
	{
		if (it.Value == targetWidget)
		{
			m_OpenedUserWidget.Add(it.Key, it.Value);
			m_PendingUserWidget.Remove(it.Key);
			break;
		}
	}

	return result;
}

bool UUIManage::CloseUI(UUserWidget* targetWidget, bool needUnload )
{
	bool result = false;
	if (targetWidget == nullptr) return result;
	targetWidget->RemoveFromParent();
	return result;
}

UUIBase* UUIManage::GetBindClass( UUserWidget* targetWidget )
{
	UUIBase* result = nullptr;

	if (targetWidget == nullptr) return result;

	for (auto& it : m_OpenedUserWidget)
	{
		if ( it.Value == targetWidget )
		{
			result = it.Key;
			break;
		}
	}
	
	return result;
}


void UUIManage::Initialize()
{
	m_OpenedUserWidget.Empty();
	m_PendingUserWidget.Empty();
	m_UserWidgetMap.Empty();

	RegisterUINativeClass();
}


void UUIManage::RegisterUINativeClass()
{
	m_UserWidgetMap.Add( EUIType_LogIn, UIBindData("UILogIn", "UILogIn") );	
} 

UUIBase* UUIManage::CreateNativeClassObject(EUIType type, UUserWidget* widget)
{
	UUIBase* result = nullptr;

	UIBindData* UIData = m_UserWidgetMap.Find(type);

	UClass* UIClass = StaticLoadClass(UUIBase::StaticClass(), NULL, *(FString("/Script/KayakGame.") + UIData->NativeUIClassName), NULL, LOAD_Quiet, NULL);
	result = NewObject<UUIBase>(GetTransientPackage(), UIClass);

	if (result != nullptr)
	{
		result->SetTargtUserWidget(widget);
		result->Initialize();
	}

	return result;
}
