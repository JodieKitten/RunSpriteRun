// Copyright KittenGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RSRPlayerController.generated.h"

/**
 * 
 */

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class ARSRCharacter;
class ARSRHUD;
class UPauseScreenWidget;
class UTimerWidget;

UCLASS()
class RUNSPRITERUN_API ARSRPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ARSRPlayerController();
	void OnGameWon();

	UFUNCTION()
	void PauseMovement(bool bShouldPause);

	UPROPERTY()
	UTimerWidget* TimerWidget;

protected:
	virtual void BeginPlay() override;
	void SetPlayInputMode();
	virtual void SetupInputComponent() override;

private:
	ARSRCharacter* ControlledCharacter;
	ARSRHUD* HUD;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UPauseScreenWidget> PauseScreenWidgetClass;

	UPROPERTY()
	UPauseScreenWidget* PauseScreenWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UTimerWidget> TimerWidgetClass;

	bool bPauseScreenOpen = false;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> MappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> MoveLeftAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> MoveRightAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> PauseAction;

	void AddSubsystemMappingContext();
	void MoveLeft(const FInputActionValue& InputActionValue);
	void MoveRight(const FInputActionValue& InputActionValue);
	void Jump(const FInputActionValue& InputActionValue);
	void PauseGame(const FInputActionValue& InputActionValue);

	void SetMenuInputMode();

	void OnGameStart();

	UFUNCTION()
	void StartGameTimer();
};
