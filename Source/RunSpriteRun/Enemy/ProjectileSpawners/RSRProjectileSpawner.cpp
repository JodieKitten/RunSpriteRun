// Copyright KittenGames


#include "RSRProjectileSpawner.h"
#include "Paper2D/Classes/PaperSpriteComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "RunSpriteRun/Enemy/Projectile/RSRProjectile.h"
#include "Kismet/GameplayStatics.h"

ARSRProjectileSpawner::ARSRProjectileSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite");
	SetRootComponent(Sprite);
	Sprite->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>("ProjectileSpawnPoint");
	ProjectileSpawnPoint->SetupAttachment(Sprite);
}

void ARSRProjectileSpawner::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ARSRProjectileSpawner::Fire, SpawnSpeed, true, SpawnSpeed);
}

void ARSRProjectileSpawner::Fire()
{	
	FActorSpawnParameters Params;
	ARSRProjectile* SpawnedProjectile = GetWorld()->SpawnActor<ARSRProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentTransform(), Params);
	SpawnedProjectile->SetLifeSpan(ProjectileLifespan);

	UGameplayStatics::PlaySoundAtLocation(
		this, ShootSound, GetActorLocation(), FRotator::ZeroRotator, ShootSoundVolumeMultiplier, ShootSoundPitchMiltiplier, 0.0f, ShootSoundAttenuation);
}
