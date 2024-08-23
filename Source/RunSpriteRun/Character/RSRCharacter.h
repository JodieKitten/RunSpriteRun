// Copyright KittenGames

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "RSRCharacter.generated.h"

class USpriteComponent;
class USpringArmComponent;
class UCameraComponent;
class UPaperFlipbook;
/**
 * 
 */

UCLASS()
class RUNSPRITERUN_API ARSRCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	ARSRCharacter();
	void SetFlipbook();
	void MoveLeft();
	void MoveRight();
	void HandleRotation();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
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


};
