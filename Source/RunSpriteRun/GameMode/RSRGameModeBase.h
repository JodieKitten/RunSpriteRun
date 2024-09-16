// Copyright KittenGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RSRGameModeBase.generated.h"

class UTimerWidget;
class URSRGameInstance;
/**
 * 
 */
UCLASS()
class RUNSPRITERUN_API ARSRGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void SetupGameWonDelegate();

protected:
	virtual void BeginPlay() override;

private:
	UTimerWidget* CurrentTimerWidget;

	URSRGameInstance* GameInstance;

	float BestTime;

	UFUNCTION()
	void SaveGameOnGameWon(float NewBestTime);

	void LoadGame();

public:
	float GetBestTime() { return BestTime; }
	void SetBestTime(float NewBestTime) { BestTime = NewBestTime; }
};
