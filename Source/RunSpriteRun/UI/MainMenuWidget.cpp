// Copyright KittenGames


#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

bool UMainMenuWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (QuitButton && !QuitButton->OnClicked.IsBound())
	{
		QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::QuitButtonClicked);
	}
	if (StartButton && !StartButton->OnClicked.IsBound())
	{
		StartButton->OnClicked.AddDynamic(this, &UMainMenuWidget::StartButtonClicked);
	}

	return true;
}

void UMainMenuWidget::QuitButtonClicked()
{
	QuitButton->SetIsEnabled(false);
	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}

void UMainMenuWidget::StartButtonClicked()
{
	StartButton->SetIsEnabled(false);
	UGameplayStatics::OpenLevel(this, FName("Main"));
}
