// Copyright KittenGames


#include "RSRMovingActor.h"
#include "Components/InterpToMovementComponent.h"
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

	InterpToMovementComponent = CreateDefaultSubobject<UInterpToMovementComponent>("InterpToMovement");
}

void ARSRMovingActor::BeginPlay()
{
	Super::BeginPlay();
	
	InterpToMovementComponent->Duration = Duration;
	InterpToMovementComponent->TeleportType = ETeleportType::None;
	InterpToMovementComponent->BehaviourType = EInterpToBehaviourType::PingPong;

	FInterpControlPoint ControlPointOne;
	ControlPointOne.PositionControlPoint = LocationOne;

	FInterpControlPoint ControlPointTwo;
	ControlPointTwo.PositionControlPoint = LocationTwo;

	InterpToMovementComponent->ControlPoints.Add(ControlPointOne);
	InterpToMovementComponent->ControlPoints.Add(ControlPointTwo);
}

void ARSRMovingActor::ResetLocationOnPlayerDeath()
{
	ARSRCharacter* Character = Cast<ARSRCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (ActorHasTag("Reset") && Character->bIsDead)
	{
		SetActorLocation(LocationOne);
		InterpToMovementComponent->Deactivate();

		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ARSRMovingActor::ReactivateInterpMovement, 1.0f, false);
	}
}

void ARSRMovingActor::ReactivateInterpMovement()
{
	InterpToMovementComponent->RestartMovement();
}

void ARSRMovingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

