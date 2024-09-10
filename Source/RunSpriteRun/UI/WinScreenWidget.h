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

public:

protected:
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	UButton* ReturnButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* RetryButton;

	UFUNCTION()
	void ReturnButtonClicked();

	UFUNCTION()
	void RetryButtonClicked();
};
