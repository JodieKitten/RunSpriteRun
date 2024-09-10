// Copyright KittenGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RSRSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class RUNSPRITERUN_API URSRSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	float BestTime = 7200.0f;
};
