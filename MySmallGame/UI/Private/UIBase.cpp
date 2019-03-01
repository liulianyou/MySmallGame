// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/UIBase.h"

#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"

UUIBase::UUIBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	WidgetOwner(nullptr)
{
}

void UUIBase::Initialize(UUIWidget* Owner)
{
	if (Owner == nullptr) return;
	WidgetOwner = Owner;

	InitializeLocalLogic();
}

bool UUIBase::parseDotString(TArray<FString>& HerichyValue, const FString Path)
{
	bool returnValue = false;

	Path.ParseIntoArray(HerichyValue, TEXT("."));

	if (HerichyValue.Num() == 0)
	{
		//FMessageLog("KayakUIError").Error("UIError::Please check the string format of UIElement's path %s in class %s", *path, this->GetName());
		return returnValue;
	}

	returnValue = true;
	return returnValue;
}


UWidget* UUIBase::GetImmediateUIElementByName(UWidget* parentWidget, const FString UIName)
{
	UWidget* result = nullptr;
	//if the parentWidget is nullptr which is indicate the UIName is the root slot name
	if (parentWidget == nullptr)
	{
		result = GetTargetUserWidget()->WidgetTree->RootWidget;

		if (result == nullptr)
		{
			//FMessageLog("KayakUIError").Error("There is no UI element in path: %s in class: %s", *path, UClass::GetName());
			return result;
		}

		if (result->GetName() == UIName) return result;

		parentWidget = result;
	}

	UUserWidget* userWidget = dynamic_cast<UUserWidget*>(parentWidget);
	if (userWidget != nullptr)
	{
		result = userWidget->WidgetTree->RootWidget;
		if (result->GetName() == UIName) return result;
		else
		{
			// FMessageLog("KayakUIError").Error("The UIName %s is not the name of root element of widget %s", *UIName, userWidget.GetDisplayLabel());
			return nullptr; 
		}
	}
	else
	{
		UPanelWidget* panelWidget = dynamic_cast<UPanelWidget*>(parentWidget);
		if (panelWidget == nullptr)
		{
			return result;
		}

		for (int i = 0; i < panelWidget->GetChildrenCount(); i++)
		{
			result = panelWidget->GetChildAt(i);
			if (result->GetName() == UIName)
			{
				break;
			}
			else
			{
				result = nullptr;
			}
		}
	}

	return result;
}

APawn* UUIBase::GetOwningPawn()
{
	UUIManage* UUIManage = GetOwningUIManager();
	if (UUIManage != nullptr)
	{
		UUIManage->HUDOwner->GetOwningPawn();
	}
	else
		return nullptr;
}

APlayerController* UUIBase::GetOwningPlayerController()
{
	UUIManage* UUIManage = GetOwningUIManager();
	if (UUIManage != nullptr)
	{
		return UUIManage->HUDOwner->GetOwningPlayerController();
	}
	else
		return nullptr;
}

UUIManage* UUIBase::GetOwningUIManager()
{
	if (WidgetOwner != nullptr)
	{
		return WidgetOwner->GetOuter();
	}
	else
		return nullptr;
}

UUserWidget* GetTargetUserWidget()
{
	if (WidgetOwner != nullptr)
	{
		return WidgetOwner->UIElement;
	}
	else
		return nullptr;
}
}

