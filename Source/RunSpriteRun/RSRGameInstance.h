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
	
public:
	URSRSaveGame* GameData;
	void LoadGame();
	void SavePlayerTimeData(float BestTimeRecorded);
	URSRSaveGame* GetGameData() { return GameData; }

protected:
	void Init() override;

private:
	void SaveGame();
	FString SaveSlot = "GameData";
};
