// Copyright KittenGames


#include "TimerWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetMathLibrary.h"
#include "RunSpriteRun/GameMode/RSRGameModeBase.h"
#include "Kismet/GameplayStatics.h"

bool UTimerWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (CurrentTimeText)
	{
		CurrentTimeText->SetText(FText::FromString(""));
		CurrentTimeText->TextDelegate.BindUFunction(this, FName("SetCurrentTimeText"));
	}

	if (BestTimeText)
	{
		BestTimeText->SetText(FText::FromString(""));
		BestTimeText->TextDelegate.BindUFunction(this, FName("SetBestTimeText"));
	}

	GameMode = Cast<ARSRGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (GameMode)
	{
		BestTime = GameMode->GetBestTime();
	}

	return true;
}

bool UTimerWidget::IsBestTimeDefaultTime()
{
	return BestTime == DefaultBestTime;
}

FText UTimerWidget::SetCurrentTimeText()
{
	if (bTimerActive)
	{
		// We want the timer to start at 0, after the initial game countdown
		CurrentTime = GetWorld()->GetTimeSeconds() - CountdownSeconds;
	}
	else
	{
		if (CurrentTime < BestTime)
		{
		 	BestTime = CurrentTime;

			OnBestTimeUpdatedDelegate.Broadcast(BestTime);
		}
	}

	FTimespan Timespan = UKismetMathLibrary::MakeTimespan(0, 0, 0, CurrentTime, 0);
	return FText::AsTimespan(Timespan);
}

FText UTimerWidget::SetBestTimeText()
{
	if (IsBestTimeDefaultTime())
	{
		return FText();
	}

	FTimespan Timespan = UKismetMathLibrary::MakeTimespan(0, 0, 0, BestTime, 0);
	return FText::AsTimespan(Timespan);
}
