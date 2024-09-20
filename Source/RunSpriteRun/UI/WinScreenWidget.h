// Copyright KittenGames

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WinScreenWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class RUNSPRITERUN_API UWinScreenWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* RetryButton;

	UPROPERTY(meta = (BindWidget))
	UButton* MainMenuButton;

	UFUNCTION()
	void QuitButtonClicked();

	UFUNCTION()
	void RetryButtonClicked();

	UFUNCTION()
	void MainMenuButtonClicked();
};
