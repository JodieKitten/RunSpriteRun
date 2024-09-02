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

UCLASS()
class RUNSPRITERUN_API ARSRPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ARSRPlayerController();
	void PauseMovement(bool bShouldPause);
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	ARSRCharacter* ControlledCharacter;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> MappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> MoveLeftAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> MoveRightAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> JumpAction;

	void MoveLeft(const FInputActionValue& InputActionValue);
	void MoveRight(const FInputActionValue& InputActionValue);
	void Jump(const FInputActionValue& InputActionValue);

};
