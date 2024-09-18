// Copyright KittenGames

#pragma once

#include "CoreMinimal.h"
#include "RSRGameModeBase.h"
#include "MainMenuGameModeBase.generated.h"

class UMainMenuWidget;
/**
 * 
 */
UCLASS()
class RUNSPRITERUN_API AMainMenuGameModeBase : public ARSRGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMainMenuWidget> MainMenuWidgetClass;

	UPROPERTY()
	UMainMenuWidget* MainMenuWidget;
	
};
