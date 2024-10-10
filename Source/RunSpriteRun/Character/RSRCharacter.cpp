// Copyright KittenGames

#include "RSRCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperSpriteComponent.h"
#include "PaperFlipbook.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "RunSpriteRun/Player/RSRPlayerController.h"

ARSRCharacter::ARSRCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
	Camera->SetProjectionMode(ECameraProjectionMode::Orthographic);
	Camera->SetOrthoWidth(FOVBase);

	HeartSprite = CreateDefaultSubobject<UPaperSpriteComponent>("HeartSprite");
	HeartSprite->SetupAttachment(RootComponent);
	HeartSprite->SetVisibility(false);
}

void ARSRCharacter::SetHeartSpriteVisible()
{
	HeartSprite->SetVisibility(true);
}

void ARSRCharacter::EnableCameraLag(bool bEnable)
{
	SpringArm->bEnableCameraLag = bEnable;
}

bool ARSRCharacter::TeleportTo(const FVector& DestLocation, const FRotator& DestRotation, bool bIsATest, bool bNoCheck)
{
	if (Super::TeleportTo(DestLocation, DestRotation, bIsATest, bNoCheck))
	{
		FTimerHandle TimerHandle;
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUFunction(this, FName("EnableCameraLag"), true);
		GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, 1.0f, false);
	}

	return false;
}

void ARSRCharacter::BeginPlay()
{
	Super::BeginPlay();
	StartingLocation = GetActorLocation();
	SetRespawnLocation(StartingLocation);
}

void ARSRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetFlipbook();
	HandleRotation();
	UpdateOrthoView(DeltaTime);
}

void ARSRCharacter::SetFlipbook()
{
	if (GetCharacterMovement()->IsFalling())
	{
		GetSprite()->SetFlipbook(JumpFlipbook);
	}
	if (bIsDead)
	{
		GetSprite()->SetFlipbook(DeathFlipbook);
	}
	if (bIsRespawning)
	{
		GetSprite()->SetFlipbook(RespawningFlipbook);
	}

	FVector CurrentVelocity = GetCharacterMovement()->Velocity;
	if (CurrentVelocity.Length() > 0)
	{
		GetSprite()->SetFlipbook(MoveFlipbook);
		PlayRunningSound();
	}
	else if (CurrentVelocity.Length() == 0 && !bIsDead && !bIsRespawning)
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
		GetSprite()->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	}
}

void ARSRCharacter::PlayRunningSound()
{
	if (GetSprite()->GetPlaybackPositionInFrames() == 1)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this, RunningSound, GetActorLocation(), RunningSoundVolumeMultiplier, RunningSoundPitchMiltiplier, 0.0f, nullptr, SoundConcurrency);
	}
}

void ARSRCharacter::RespawnCharacter()
{
	SetActorLocation(RespawnLocation);
	bIsDead = false;
	bIsRespawning = true;

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ARSRCharacter::SetRespawnToFalse, 0.3f, false);
}

void ARSRCharacter::SetRespawnToFalse()
{
	bIsRespawning = false;
	PauseMovement(false);
}

void ARSRCharacter::PauseMovement(bool bShouldPause)
{
	if (ARSRPlayerController* PlayerController = Cast<ARSRPlayerController>(GetController()))
	{
		PlayerController->PauseMovement(bShouldPause);
	}
}

void ARSRCharacter::UpdateOrthoView(float DeltaTime)
{
	if (Camera)
	{
		Camera->SetOrthoWidth(FMath::FInterpTo(Camera->OrthoWidth, TargetOrthoView, DeltaTime, InterpSpeed));
	}
}

void ARSRCharacter::ChangeCameraView()
{
	TargetOrthoView = FOVAirbone;
}

void ARSRCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	TargetOrthoView = FOVBase;
}

void ARSRCharacter::Die()
{
	bIsDead = true;
	PauseMovement(true);

	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation(), FRotator::ZeroRotator);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ARSRCharacter::RespawnCharacter, 0.3f, false);
}

void ARSRCharacter::SetRespawnLocation(FVector InRespawnLocation)
{
	RespawnLocation = InRespawnLocation;
}

void ARSRCharacter::Move(FVector Direction, bool InIsMovingLeft)
{
	AddMovementInput(Direction);
	bIsMovingLeft = InIsMovingLeft;
}
