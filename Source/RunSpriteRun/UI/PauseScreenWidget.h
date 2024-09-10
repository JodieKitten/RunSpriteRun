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
	UButton* ReturnButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ContinueButton;

	UFUNCTION()
	void ReturnButtonClicked();

	UFUNCTION()
	void ContinueButtonClicked();

	UTimerWidget* TimerWidget;
};
