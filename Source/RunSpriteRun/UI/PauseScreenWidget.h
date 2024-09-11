// Copyright KittenGames

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseScreenWidget.generated.h"

class UButton;
class UTimerWidget;

/**
 * 
 */
UCLASS()
class RUNSPRITERUN_API UPauseScreenWidget : public UUserWidget
{
	GENERATED_BODY()

public:

protected:
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ContinueButton;

	UPROPERTY(meta = (BindWidget))
	UButton* MainMenuButton;

	UFUNCTION()
	void QuitButtonClicked();

	UFUNCTION()
	void ContinueButtonClicked();

	UFUNCTION()
	void MainMenuButtonClicked();

	UTimerWidget* TimerWidget;
};
