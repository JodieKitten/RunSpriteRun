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
	void AddGameStartOverlay();
	void AddTimerOverlay();
	void AddKeyFoundOverlay();
	void AddKeyNeededOverlay();
	void AddWinScreenOverlay();

private:
	UPROPERTY()
	UUserWidget* GameStartWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> GameStartClass;

	// Set to the same float as the countdown itself
	UPROPERTY(EditAnywhere)
	float GameStartWidgetDuration = 3.0f;

	UPROPERTY()
	UUserWidget* TimerWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> TimerWidgetClass;

	UPROPERTY()
	UUserWidget* KeyFoundWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> KeyFoundClass;

	UPROPERTY(EditAnywhere)
	float KeyFoundWidgetDuration = 5.0f;

	UPROPERTY()
	UUserWidget* KeyNeededWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> KeyNeededClass;

	UPROPERTY(EditAnywhere)
	float KeyNeededWidgetDuration = 5.0f;

	UPROPERTY()
	UWinScreenWidget* WinScreenWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UWinScreenWidget> WinScreenClass;

	UFUNCTION()
	void RemoveWidgetFromParent(UUserWidget* WidgetToRemove);

	void CreateWidgetAndAddToViewport(UUserWidget* Widget, TSubclassOf<UUserWidget> WidgetClass, bool bRemove = true, float Duration = 5.0f);
};
