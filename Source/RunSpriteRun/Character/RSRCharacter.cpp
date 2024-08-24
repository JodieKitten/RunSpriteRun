// Copyright KittenGames

#include "RSRCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "GameFramework/CharacterMovementComponent.h"

ARSRCharacter::ARSRCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
	Camera->SetProjectionMode(ECameraProjectionMode::Perspective);
	Camera->SetFieldOfView(90.0f);
}

void ARSRCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void ARSRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetFlipbook();
	HandleRotation();
}

void ARSRCharacter::SetFlipbook()
{
	if (GetCharacterMovement()->IsFalling())
	{
		GetSprite()->SetFlipbook(JumpFlipbook);
	}

	FVector CurrentVelocity = GetCharacterMovement()->Velocity;
	if (CurrentVelocity.Length() > 0)
	{
		GetSprite()->SetFlipbook(MoveFlipbook);
	}
	else if (CurrentVelocity.Length() == 0)
	{
		GetSprite()->SetFlipbook(IdleFlipbook);
	}
}

void ARSRCharacter::Jump()
{
	Super::Jump();
}

void ARSRCharacter::HandleRotation()
{
	if (GetCharacterMovement()->Velocity.X < 0.0f || ((GetCharacterMovement()->Velocity.X == 0.0f && bIsMovingLeft)))
	{
		GetSprite()->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	}
	else if (GetCharacterMovement()->Velocity.X > 0.0f || ((GetCharacterMovement()->Velocity.X == 0.0f && !bIsMovingLeft)))
	{
		GetSprite()->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f));
	}
}

void ARSRCharacter::Move(FVector Direction, bool InIsMovingLeft)
{
	AddMovementInput(Direction);
	bIsMovingLeft = InIsMovingLeft;
}
