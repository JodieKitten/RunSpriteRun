// Copyright KittenGames


#include "RSRMovingActor.h"
#include "Paper2D/Classes/PaperSpriteComponent.h"
#include "RunSpriteRun/Character/RSRCharacter.h"
#include "Kismet/GameplayStatics.h"

ARSRMovingActor::ARSRMovingActor()
{
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>("DefaultSceneComponent");
	SetRootComponent(DefaultSceneComponent);

	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite");
	Sprite->SetupAttachment(DefaultSceneComponent);
	Sprite->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	InterpToMovementComponent = CreateDefaultSubobject<UInterpToMovementComponent>("InterpToMovement");
	InterpToMovementComponent->Duration = Duration;
	InterpToMovementComponent->TeleportType = ETeleportType::None;
	InterpToMovementComponent->BehaviourType = EInterpToBehaviourType::PingPong;

	InterpToMovementComponent->ControlPoints.Add(ControlPointOne);
	InterpToMovementComponent->ControlPoints.Add(ControlPointTwo);
}

void ARSRMovingActor::BeginPlay()
{
	Super::BeginPlay();
}

void ARSRMovingActor::ResetLocationOnPlayerDeath()
{
	ARSRCharacter* Character = Cast<ARSRCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (ActorHasTag("Reset") && Character->bIsDead)
	{
		// Resets moving platforms back to their original position, to avoid the player having to wait for them to return
		SetActorLocation(LocationOne);
		InterpToMovementComponent->StopMovementImmediately();

		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ARSRMovingActor::ReactivateInterpMovement, ResetInterpDelay, false);
	}
}

void ARSRMovingActor::ReactivateInterpMovement()
{
	InterpToMovementComponent->RestartMovement();
}

void ARSRMovingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ResetLocationOnPlayerDeath();
}

