// Copyright KittenGames

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimerWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBestTimeUpdatedDelegate, float, NewBestTime);

class UTextBlock;
class ARSRGameModeBase;

/**
 * 
 */
UCLASS()
class RUNSPRITERUN_API UTimerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	bool bTimerActive = false;

	UPROPERTY()
	FOnBestTimeUpdatedDelegate OnBestTimeUpdatedDelegate;

protected:
	virtual bool Initialize() override;

private:
	ARSRGameModeBase* GameMode;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentTimeText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* BestTimeText;

	float CurrentTime = 0.0f;

	float BestTime;

	float DefaultBestTime = 7200.0f;

	UPROPERTY(EditAnywhere)
	float CountdownSeconds = 3.0f;

	bool IsBestTimeDefaultTime();

	UFUNCTION()
	FText SetCurrentTimeText();

	UFUNCTION()
	FText SetBestTimeText();
};
