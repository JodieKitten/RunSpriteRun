// Copyright KittenGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RSRProjectileSpawner.generated.h"

class UPaperSpriteComponent;
class ARSRProjectile;
class USoundWave;
class USoundAttenuation;

UCLASS()
class RUNSPRITERUN_API ARSRProjectileSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ARSRProjectileSpawner();

protected:
	virtual void BeginPlay() override;

private:
	void Fire();

	UPROPERTY(EditDefaultsOnly)
	UPaperSpriteComponent* Sprite;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, Category = Projectile)
	TSubclassOf<ARSRProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = Projectile)
	USoundWave* ShootSound;

	UPROPERTY(EditAnywhere, Category = Projectile)
	USoundAttenuation* ShootSoundAttenuation;

	UPROPERTY(EditAnywhere)
	float SpawnSpeed = 2.0f;

	UPROPERTY(EditAnywhere)
	float ProjectileLifespan = 3.0f;

	UPROPERTY(EditAnywhere)
	float ShootSoundVolumeMultiplier = 0.8f;

	UPROPERTY(EditAnywhere)
	float ShootSoundPitchMiltiplier = 1.0f;
};
