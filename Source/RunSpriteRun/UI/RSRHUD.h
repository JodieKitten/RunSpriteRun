// Copyright KittenGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RSRHUD.generated.h"

class UWinScreenWidget;
/**
 * 
 */
UCLASS()
class RUNSPRITERUN_API ARSRHUD : public AHUD
{
	GENERATED_BODY()

public:
	/* Game start */
	void AddGameStartOverlay();

	UPROPERTY()
	UUserWidget* GameStartWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget>
	GameStartClass;
	/* Win Screen end */

	/* Timer */
	void AddTimerOverlay();

	UPROPERTY()
	UUserWidget* TimerWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> TimerWidgetClass;
	/* Timer end */

	/* Key Found */
	void AddKeyFoundOverlay();

	UPROPERTY()
	UUserWidget* KeyFoundWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> KeyFoundClass;
	/* Key Found end */

	/* Key Needed */
	void AddKeyNeededOverlay();

	UPROPERTY()
	UUserWidget* KeyNeededWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> KeyNeededClass;
	/* Key Needed end*/

	/* Win Screen */
	void AddWinScreenOverlay();

	UPROPERTY()
	UWinScreenWidget* WinScreenWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UWinScreenWidget> WinScreenClass;
	/* Win Screen end */

	UFUNCTION()
	void RemoveWidgetFromParent(UUserWidget* WidgetToRemove);

	void CreateWidgetAndAddToViewport(UUserWidget* Widget, TSubclassOf<UUserWidget> WidgetClass, bool bRemove = true, float Duration = 5.0f);

	UPROPERTY(EditAnywhere)
	float DelayDuration = 5.0f;
};
