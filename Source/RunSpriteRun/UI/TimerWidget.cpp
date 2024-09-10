// Copyright KittenGames


#include "TimerWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetMathLibrary.h"
#include "RunSpriteRun/RSRGameInstance.h"
#include "RunSpriteRun/RSRSaveGame.h"

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

	if (URSRGameInstance* GameInstance = Cast<URSRGameInstance>(GetGameInstance()))
	{
		GameInstance->LoadGame();
		BestTime = GameInstance->GetGameData()->BestTime;
	}

	return true;
}

void UTimerWidget::Tick(FGeometry MyGeometry, float InDeltaTime)
{
	Super::Tick(MyGeometry, InDeltaTime);

	SetCurrentTimeText();
}

bool UTimerWidget::BestTimeNotSet()
{
	return BestTime == 7200.0f;
}

FText UTimerWidget::SetCurrentTimeText()
{
	if (bTimerActive)
	{
		CurrentTime = GetWorld()->GetTimeSeconds() - 3.0f;
	}
	else
	{
		CurrentTime = CurrentTime;

		if (CurrentTime < BestTime)
		{
			BestTime = CurrentTime;
			if (URSRGameInstance* GameInstance = Cast<URSRGameInstance>(GetGameInstance()))
			{
				GameInstance->SavePlayerTimeData(BestTime);
			}
		}
	}

	FTimespan Timespan = UKismetMathLibrary::MakeTimespan(0, 0, 0, CurrentTime, 0);
	return FText::AsTimespan(Timespan);
}

FText UTimerWidget::SetBestTimeText()
{
	// if BestTime hasn't been overwritten yet, set to an empty FText
	if (BestTimeNotSet())
	{
		return FText();
	}

	FTimespan Timespan = UKismetMathLibrary::MakeTimespan(0, 0, 0, BestTime, 0);

	return FText::AsTimespan(Timespan);
}
