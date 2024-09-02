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

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>("ProjectileSpawnPoint");
	ProjectileSpawnPoint->SetupAttachment(Sprite);
}

void ARSRProjectileSpawner::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ARSRProjectileSpawner::Fire, 2.0f, true, 2.0f);
}

void ARSRProjectileSpawner::Fire()
{	
	FActorSpawnParameters Params;
	GetWorld()->SpawnActor<ARSRProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentTransform(), Params);

	UGameplayStatics::PlaySoundAtLocation(this, ShootSound, GetActorLocation(), FRotator::ZeroRotator);
}

