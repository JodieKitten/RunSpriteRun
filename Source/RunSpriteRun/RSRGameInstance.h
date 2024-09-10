// Copyright KittenGames

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RSRGameInstance.generated.h"

class URSRSaveGame;

/**
 * 
 */
UCLASS()
class RUNSPRITERUN_API URSRGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	void Init() override;

	FString SaveSlot = "GameData";

	URSRSaveGame* GameData;

public:
	UPROPERTY()
	float BestTime;

	void SaveGame();
	void LoadGame();
	void SavePlayerTimeData(float BestTimeRecorded);
	URSRSaveGame* GetGameData() { return GameData; }
};
