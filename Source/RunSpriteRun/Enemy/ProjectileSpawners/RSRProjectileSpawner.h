// Copyright KittenGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RSRProjectileSpawner.generated.h"

class UPaperSpriteComponent;
class ARSRProjectile;
class USoundWave;

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


};
