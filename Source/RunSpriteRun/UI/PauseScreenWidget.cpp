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

	if (ReturnButton && !ReturnButton->OnClicked.IsBound())
	{
		ReturnButton->OnClicked.AddDynamic(this, &UPauseScreenWidget::ReturnButtonClicked);
	}
	if (ContinueButton && !ContinueButton->OnClicked.IsBound())
	{
		ContinueButton->OnClicked.AddDynamic(this, &UPauseScreenWidget::ContinueButtonClicked);
	}

	return true;
}

void UPauseScreenWidget::ReturnButtonClicked()
{
	ReturnButton->SetIsEnabled(false);
	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}

void UPauseScreenWidget::ContinueButtonClicked()
{
	UGameplayStatics::SetGamePaused(this, false);
	RemoveFromParent();
}
