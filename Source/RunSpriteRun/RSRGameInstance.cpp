// Copyright KittenGames


#include "RSRGameInstance.h"
#include "RSRSaveGame.h"
#include "Kismet/GameplayStatics.h"

void URSRGameInstance::Init()
{
	Super::Init();
	//LoadGame();
}

void URSRGameInstance::SaveGame()
{
	UGameplayStatics::SaveGameToSlot(GameData, SaveSlot, 0);
}

void URSRGameInstance::LoadGame()
{
	if (UGameplayStatics::DoesSaveGameExist(SaveSlot, 0))
	{
		GameData = Cast<URSRSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlot, 0));
	}
	else
	{
		GameData = Cast<URSRSaveGame>(UGameplayStatics::CreateSaveGameObject(URSRSaveGame::StaticClass()));
	}
}

void URSRGameInstance::SavePlayerTimeData(float BestTimeRecorded)
{
	if (GameData)
	{
		GameData->BestTime = BestTimeRecorded;
		SaveGame();
	}
}
