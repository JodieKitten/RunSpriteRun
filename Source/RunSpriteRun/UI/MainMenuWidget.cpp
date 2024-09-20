// Copyright KittenGames


#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetMathLibrary.h"
#include "RunSpriteRun/Player/RSRPlayerController.h"
#include "RunSpriteRun/GameMode/RSRGameModeBase.h"

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
	if (BestTimeText)
	{
		BestTimeText->SetText(FText::FromString(""));
		BestTimeText->TextDelegate.BindUFunction(this, FName("SetBestTimeText"));
	}

	SetIsFocusable(true);

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

FText UMainMenuWidget::SetBestTimeText()
{
	ARSRGameModeBase* GameMode = Cast<ARSRGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (GameMode)
	{
		BestTime = GameMode->GetBestTime();
	}

	if (BestTime == 7200.0f)
	{
		return FText::FromString("No time set!");
	}

	FTimespan Timespan = UKismetMathLibrary::MakeTimespan(0, 0, 0, BestTime, 0);

	return FText::AsTimespan(Timespan);
}
