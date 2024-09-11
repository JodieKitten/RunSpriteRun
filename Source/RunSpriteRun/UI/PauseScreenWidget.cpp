// Copyright KittenGames


#include "PauseScreenWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "TimerWidget.h"

bool UPauseScreenWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (QuitButton && !QuitButton->OnClicked.IsBound())
	{
		QuitButton->OnClicked.AddDynamic(this, &UPauseScreenWidget::QuitButtonClicked);
	}
	if (ContinueButton && !ContinueButton->OnClicked.IsBound())
	{
		ContinueButton->OnClicked.AddDynamic(this, &UPauseScreenWidget::ContinueButtonClicked);
	}
	if (MainMenuButton && !MainMenuButton->OnClicked.IsBound())
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UPauseScreenWidget::MainMenuButtonClicked);
	}

	return true;
}

void UPauseScreenWidget::QuitButtonClicked()
{
	QuitButton->SetIsEnabled(false);
	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}

void UPauseScreenWidget::ContinueButtonClicked()
{
	UGameplayStatics::SetGamePaused(this, false);
	RemoveFromParent();
}

void UPauseScreenWidget::MainMenuButtonClicked()
{
	MainMenuButton->SetIsEnabled(false);
	UGameplayStatics::OpenLevel(this, FName("Menu"));
}
