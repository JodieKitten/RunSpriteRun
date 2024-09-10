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

	if (ReturnButton && !ReturnButton->OnClicked.IsBound())
	{
		ReturnButton->OnClicked.AddDynamic(this, &UWinScreenWidget::ReturnButtonClicked);
	}
	if (RetryButton && !RetryButton->OnClicked.IsBound())
	{
		RetryButton->OnClicked.AddDynamic(this, &UWinScreenWidget::RetryButtonClicked);
	}

	return true;
}

void UWinScreenWidget::ReturnButtonClicked()
{
	ReturnButton->SetIsEnabled(false);
	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}

void UWinScreenWidget::RetryButtonClicked()
{
	RetryButton->SetIsEnabled(false);
	UGameplayStatics::OpenLevel(this, FName("Main"));
}
