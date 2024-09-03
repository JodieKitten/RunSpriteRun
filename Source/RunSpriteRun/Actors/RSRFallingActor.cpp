// Copyright KittenGames


#include "RSRFallingActor.h"
#include "RunSpriteRun/Character/RSRCharacter.h"
#include "Paper2D/Classes/PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

#include "GameplayTask.h"
#include "Tasks/GameplayTask_WaitDelay.h"

ARSRFallingActor::ARSRFallingActor()
{
	PrimaryActorTick.bCanEverTick = false;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>("DefaultRootComponent");
	SetRootComponent(DefaultRoot);

	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite");
	Sprite->SetupAttachment(DefaultRoot);

	DamageBox = CreateDefaultSubobject<UBoxComponent>("DamageBox");
	DamageBox->SetupAttachment(Sprite);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>("TriggerBox");
	TriggerBox->SetupAttachment(DefaultRoot);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->ProjectileGravityScale = 1.0f;
}

void ARSRFallingActor::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ARSRFallingActor::OnTriggerBoxOverlap);

	if (DamageBox)
	{
		DamageBox->OnComponentBeginOverlap.AddDynamic(this, &ARSRFallingActor::OnSphereOverlap);
	}

	ProjectileMovementComponent->Deactivate();
	StartingTransform = GetActorTransform();
	
}

void ARSRFallingActor::OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex,
	bool bFromSweep, 
	const FHitResult& SweepResult)
{

	if (ARSRCharacter* Character = Cast<ARSRCharacter>(OtherActor))
	{
		if (bIsAlreadyOverlapping)
		{
			return; // Avoid handling the overlap again
		}

		bIsAlreadyOverlapping = true;

		// Set lifespan to just over the respawn delay so respawn is still triggered
		SetLifeSpan(RespawnDelay + 1.0f);

		if (DropDelay > 0.0f)
		{
			FTimerHandle DropTimerHandle;
			GetWorldTimerManager().SetTimer(DropTimerHandle, this, &ARSRFallingActor::DelayedDrop, DropDelay, false);
		}
		else
		{
			ProjectileMovementComponent->Activate();
			UGameplayStatics::PlaySoundAtLocation(this, FallingSound, GetActorLocation(), FRotator::ZeroRotator);	
		}

		FTimerHandle RespawnTimerHandle;
		GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ARSRFallingActor::SpawnFallingActor, RespawnDelay, false);
	}
}

void ARSRFallingActor::SpawnFallingActor()
{
	FActorSpawnParameters Params;
	GetWorld()->SpawnActor<ARSRFallingActor>(FallingActorClass, StartingTransform, Params);

	// Reset overlap flag
	bIsAlreadyOverlapping = false;
}

void ARSRFallingActor::DelayedDrop()
{
	ProjectileMovementComponent->Activate();
	UGameplayStatics::PlaySoundAtLocation(this, FallingSound, GetActorLocation(), FRotator::ZeroRotator);
}

void ARSRFallingActor::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, 
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	IDamageInterface::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}
