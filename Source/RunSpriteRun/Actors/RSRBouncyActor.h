// Copyright KittenGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RSRBouncyActor.generated.h"


class UPaperSpriteComponent;
class USoundBase;
class UPaperSprite;
class ARSRCharacter;
class UBoxComponent;

UCLASS()
class RUNSPRITERUN_API ARSRBouncyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ARSRBouncyActor();

protected:
	virtual void BeginPlay() override;

private:
	ARSRCharacter* Character;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere)
	UPaperSpriteComponent* Sprite;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* OverlapBox;

	UPROPERTY(EditAnywhere)
	float LaunchVelocityZ = 800.0f;

	UPROPERTY(EditAnywhere)
	float LaunchVelocityX = 0.0f;

	UPROPERTY(EditAnywhere)
	float DelayDuration = 1.0f;

	UPROPERTY(VisibleAnywhere)
	bool bIsAirborne = false;

	UPROPERTY(EditAnywhere)
	USoundBase* BoingSound;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UPaperSprite> TrampolineUp;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UPaperSprite> TrampolineDown;

	UFUNCTION()
	void OnComponentOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	void ChangeCameraView();
	void ResetTrampoline();
};
