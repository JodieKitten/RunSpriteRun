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

	FVector StartingLocation;
	void SetRespawnLocation(FVector InRespawnLocation);

	UFUNCTION(BlueprintCallable)
	void RespawnCharacter();

	void ChangeCameraView();
	virtual void Landed(const FHitResult& Hit) override;

	UFUNCTION(BlueprintCallable)
	void Die();
	bool bIsDead = false;

	bool bHasKey = false;

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
	UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArm;

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

	bool bIsMovingLeft = false;

	bool bIsRespawning = false;

	UPROPERTY(VisibleAnywhere)
	float FOVBase = 300.0f;

	UPROPERTY(EditAnywhere)
	float FOVAirbone = 500.0f;

	float TargetSpringArmLength;

	UPROPERTY(EditAnywhere)
	float InterpSpeed = 5.0f;

	void UpdateSpringArmLength(float DeltaTime);
};
