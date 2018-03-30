#include "../Public/UILogIn.h"

#define LOCTEXT_NAMESPACE "UI"


UUILogIn::UUILogIn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	m_StartGameButton = nullptr;
	m_OptionButton = nullptr;
	m_EndGameButton = nullptr;
}

void UUILogIn::InitializeLocalLogic()
{
	m_StartGameButton = MapUIElementToLocalVariable<UButton>("Content.VerticalBoxFrame.StartGameButton.Content.Button_1");
	m_OptionButton = MapUIElementToLocalVariable<UButton>("Content.VerticalBoxFrame.OptionButton.Content.Button_1");
	m_EndGameButton = MapUIElementToLocalVariable<UButton>("Content.VerticalBoxFrame.EndGameButton.Content.Button_1");

	m_StartGameButton->OnClicked.AddDynamic(this, &UUILogIn::ClickStartGameButton);

	GetTargetUserWidget()->AnimationStartedDelegate.AddUObject(this, &UUILogIn::AnimationStart);
}

void UUILogIn::ClickStartGameButton()
{
	int a = 0;
}

void UUILogIn::AnimationStart( const UWidgetAnimation* animation)
{
	int a = 0;
}

#undef LOCTEXT_NAMESPACE 