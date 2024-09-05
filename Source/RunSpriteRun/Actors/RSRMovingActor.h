// Copyright KittenGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InterpToMovementComponent.h"
#include "RSRMovingActor.generated.h"

class UInterpToMovementComponent;
class UPaperSpriteComponent;
struct FInterpControlPoint;

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

	void ResetLocationOnPlayerDeath();
	void ReactivateInterpMovement();

	FInterpControlPoint ControlPointOne;
	FInterpControlPoint ControlPointTwo;
};
