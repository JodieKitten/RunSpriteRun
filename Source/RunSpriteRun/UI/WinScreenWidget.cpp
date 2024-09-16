// Copyright KittenGames


#include "WinScreenWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "TimerWidget.h"

bool UWinScreenWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (QuitButton && !QuitButton->OnClicked.IsBound())
	{
		QuitButton->OnClicked.AddDynamic(this, &UWinScreenWidget::QuitButtonClicked);
	}
	if (RetryButton && !RetryButton->OnClicked.IsBound())
	{
		RetryButton->OnClicked.AddDynamic(this, &UWinScreenWidget::RetryButtonClicked);
	}
	if (MainMenuButton && !MainMenuButton->OnClicked.IsBound())
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UWinScreenWidget::MainMenuButtonClicked);
	}

	return true;
}

void UWinScreenWidget::QuitButtonClicked()
{
	QuitButton->SetIsEnabled(false);
	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}

void UWinScreenWidget::RetryButtonClicked()
{
	RetryButton->SetIsEnabled(false);
	UGameplayStatics::OpenLevel(this, FName("testmap"));
}

void UWinScreenWidget::MainMenuButtonClicked()
{
	MainMenuButton->SetIsEnabled(false);
	UGameplayStatics::OpenLevel(this, FName("Menu"));
}
