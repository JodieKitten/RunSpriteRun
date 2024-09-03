// Copyright KittenGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RSRMovingActor.generated.h"

class UInterpToMovementComponent;
class UPaperSpriteComponent;

UCLASS()
class RUNSPRITERUN_API ARSRMovingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ARSRMovingActor();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	UInterpToMovementComponent* InterpToMovementComponent;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* DefaultSceneComponent;

	UPROPERTY(EditAnywhere)
	UPaperSpriteComponent* Sprite;

	UPROPERTY(EditAnywhere)
	float Duration = 3.0f;

	UPROPERTY(EditAnywhere)
	FVector LocationOne;

	UPROPERTY(EditAnywhere)
	FVector LocationTwo;

	void ResetLocationOnPlayerDeath();
	void ReactivateInterpMovement();
};
