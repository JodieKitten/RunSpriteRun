// Copyright KittenGames


#include "RSRFallingActor.h"
#include "RunSpriteRun/Character/RSRCharacter.h"
#include "Paper2D/Classes/PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

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
		if (DropDelay > 0.0f)
		{
			FTimerHandle TimerHandle;
			GetWorldTimerManager().SetTimer(TimerHandle, this, &ARSRFallingActor::DelayedDrop, DropDelay, false);
		}

		ProjectileMovementComponent->Activate();
		UGameplayStatics::PlaySoundAtLocation(this, FallingSound, GetActorLocation(), FRotator::ZeroRotator);

		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ARSRFallingActor::SpawnFallingActor, RespawnDelay, false);
	}
}

void ARSRFallingActor::SpawnFallingActor()
{
	//Destroy();

	FActorSpawnParameters Params;
	GetWorld()->SpawnActor<ARSRFallingActor>(FallingActorClass, StartingTransform, Params);
}

void ARSRFallingActor::DelayedDrop()
{
	// this function does nothing
	// we just need to delay the activation of the overlap function so platforms do not drop immediately
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
