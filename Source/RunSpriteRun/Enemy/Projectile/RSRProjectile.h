// Copyright KittenGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RunSpriteRun/Interface/DamageInterface.h"
#include "RSRProjectile.generated.h"

class UProjectileMovementComponent;
class UPaperFlipbookComponent;
class USphereComponent;
class USceneComponent;

UCLASS()
class RUNSPRITERUN_API ARSRProjectile : public AActor, public IDamageInterface
{
	GENERATED_BODY()
	
public:	
	ARSRProjectile();

	// Allow edit to lifespan from the spawner itself
	UPROPERTY(EditAnywhere)
	float Lifespan = 3.0f;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;

	UPROPERTY(EditDefaultsOnly)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SceneComponent;

	UPROPERTY(EditDefaultsOnly)
	UPaperFlipbookComponent* Flipbook;

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* Sphere;


	
};
