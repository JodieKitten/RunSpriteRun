// Copyright KittenGames

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimerWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class RUNSPRITERUN_API UTimerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void Tick(FGeometry MyGeometry, float InDeltaTime);
	bool BestTimeNotSet();

	float CurrentTime = 0.0f;

	UPROPERTY()
	float BestTime = 7200.0f;

	bool bTimerActive = false;

	UFUNCTION()
	FText SetCurrentTimeText();

	UFUNCTION()
	FText SetBestTimeText();

protected:
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentTimeText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* BestTimeText;

	FTimerHandle GameTimer;
};
