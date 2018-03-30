// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/UIBase.h"

UUIBase::UUIBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	m_TargetUserWidget = nullptr;
}

bool UUIBase::parseDotString(TArray<FString>& herichyValue, const FString path)
{
	bool returnValue = false;

	path.ParseIntoArray(herichyValue, TEXT("."));

	if (herichyValue.Num() == 0)
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
		result = m_TargetUserWidget->WidgetTree->RootWidget;

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



