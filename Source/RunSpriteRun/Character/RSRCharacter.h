// Copyright KittenGames

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "RSRCharacter.generated.h"


class USpriteComponent;
class USpringArmComponent;
class UCameraComponent;
class UPaperFlipbook;
class USoundWave;

/**
 * 
 */


UCLASS()
class RUNSPRITERUN_API ARSRCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	ARSRCharacter();
	void Move(FVector Direction, bool InIsMovingLeft);
	virtual void Jump() override;
	void Die();
	void SetRespawnLocation(FVector InRespawnLocation);

	bool bIsDead = false;
	bool bIsRespawning = false;

	UFUNCTION(BlueprintCallable)
	void RespawnCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void SetFlipbook();
	void HandleRotation();

	void SetRespawnToFalse();
	void PauseMovement(bool bShouldPause);

	UPROPERTY(EditAnywhere, Category = Character)
	USoundWave* DeathSound;

	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* Camera;

	bool bIsMovingLeft = false;

	UPROPERTY(EditAnywhere, Category = Flipbooks)
	TObjectPtr<UPaperFlipbook> IdleFlipbook;

	UPROPERTY(EditAnywhere, Category = Flipbooks)
	TObjectPtr<UPaperFlipbook> MoveFlipbook;

	UPROPERTY(EditAnywhere, Category = Flipbooks)
	TObjectPtr<UPaperFlipbook> JumpFlipbook;

	UPROPERTY(EditAnywhere, Category = Flipbooks)
	TObjectPtr<UPaperFlipbook> DeathFlipbook;

	UPROPERTY(EditAnywhere, Category = Flipbooks)
	TObjectPtr<UPaperFlipbook> RespawningFlipbook;

	FVector RespawnLocation;
};
