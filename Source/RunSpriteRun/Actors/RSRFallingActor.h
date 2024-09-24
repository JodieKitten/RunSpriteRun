// Copyright KittenGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RunSpriteRun/Interface/DamageInterface.h"
#include "RSRFallingActor.generated.h"

class UBoxComponent;
class UPaperSpriteComponent;
class UProjectileMovementComponent;
class USoundWave;

UCLASS()
class RUNSPRITERUN_API ARSRFallingActor : public AActor, public IDamageInterface
{
	GENERATED_BODY()
	
public:	
	ARSRFallingActor();

	UFUNCTION()
	void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;

protected:
	virtual void BeginPlay() override;

private:
	bool bHasSpawned = false;
	bool bIsAlreadyOverlapping = false;

	FTransform StartingTransform;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* DefaultRoot;

	UPROPERTY(EditDefaultsOnly)
	UPaperSpriteComponent* Sprite;

	UPROPERTY(EditAnywhere)
	UBoxComponent* TriggerBox;

	UPROPERTY(EditAnywhere)
	UBoxComponent* DamageBox;

	UPROPERTY(EditDefaultsOnly)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere)
	USoundWave* FallingSound;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ARSRFallingActor> FallingActorClass;

	UFUNCTION()
	void OnTriggerBoxOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	void SpawnFallingActor();

	void DelayedDrop();

	UPROPERTY(EditAnywhere)
	float RespawnDelay = 4.0f;

	UPROPERTY(EditAnywhere)
	bool bUseDropDelay = false;

	UPROPERTY(EditAnywhere)
	float DropDelay = 0.0f;

	UPROPERTY(EditAnywhere)
	float DropSoundVolumeMultiplier = 0.5f;

};
