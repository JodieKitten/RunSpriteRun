// Copyright KittenGames

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UButton;
class UTextBlock;

/**
 * 
 */
UCLASS()
class RUNSPRITERUN_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	UButton* StartButton;

	UFUNCTION()
	void QuitButtonClicked();

	UFUNCTION()
	void StartButtonClicked();

	UPROPERTY(meta = (BindWidget))
	UTextBlock* BestTimeText;

	UFUNCTION()
	FText SetBestTimeText();

	float BestTime;
};
