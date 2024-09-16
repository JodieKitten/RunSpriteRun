// Copyright KittenGames


#include "RSRGameModeBase.h"
#include "RunSpriteRun/RSRGameInstance.h"
#include "RunSpriteRun/RSRSaveGame.h"
#include "RunSpriteRun/Player/RSRPlayerController.h"
#include "RunSpriteRun/UI/TimerWidget.h"
#include "Kismet/GameplayStatics.h"


void ARSRGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = Cast<URSRGameInstance>(GetGameInstance());

	LoadGame();
}

void ARSRGameModeBase::SaveGameOnGameWon(float NewBestTime)
{
	if (GameInstance)
	{
		GameInstance->SavePlayerTimeData(NewBestTime);
	}
}

void ARSRGameModeBase::SetupGameWonDelegate()
{
	ARSRPlayerController* PlayerController = Cast<ARSRPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerController && PlayerController->TimerWidget)
	{
		CurrentTimerWidget = PlayerController->TimerWidget;
		CurrentTimerWidget->OnBestTimeUpdatedDelegate.AddDynamic(this, &ARSRGameModeBase::SaveGameOnGameWon);
	}
}

void ARSRGameModeBase::LoadGame()
{
	if (GameInstance)
	{
		GameInstance->LoadGame();
		BestTime = GameInstance->GetGameData()->BestTime;
	}
}
