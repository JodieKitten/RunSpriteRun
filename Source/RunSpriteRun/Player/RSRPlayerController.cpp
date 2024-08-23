// Fill out your copyright notice in the Description page of Project Settings.

#include "RSRPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

ARSRPlayerController::ARSRPlayerController()
{

}

void ARSRPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(MappingContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);

	Subsystem->AddMappingContext(MappingContext, 0);
	bShowMouseCursor = false;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::LockOnCapture);
	InputModeData.SetHideCursorDuringCapture(true);
	SetInputMode(InputModeData);
}

void ARSRPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARSRPlayerController::Move);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ARSRPlayerController::Jump);
}

void ARSRPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void ARSRPlayerController::Jump(const FInputActionValue& InputActionValue)
{
	const FVector InputAxisVector = InputActionValue.Get<FVector>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector UpDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Z);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(UpDirection, InputAxisVector.Z);
	}
}
