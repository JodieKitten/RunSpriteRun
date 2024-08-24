// Fill out your copyright notice in the Description page of Project Settings.

#include "RSRPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "RunSpriteRun/Character/RSRCharacter.h"

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

	ControlledCharacter = Cast<ARSRCharacter>(GetCharacter());
}

void ARSRPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveLeftAction, ETriggerEvent::Triggered, this, &ARSRPlayerController::MoveLeft);
	EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &ARSRPlayerController::MoveRight);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ARSRPlayerController::Jump);
}

void ARSRPlayerController::MoveLeft(const FInputActionValue& InputActionValue)
{
	if (ControlledCharacter)
	{
		ControlledCharacter->Move(FVector(-1.0f, 0.0f, 0.0f), true);
	}
}

void ARSRPlayerController::MoveRight(const FInputActionValue& InputActionValue)
{
	if (ControlledCharacter)
	{
		ControlledCharacter->Move(FVector(1.0f, 0.0f, 0.0f), true);
	}
}

void ARSRPlayerController::Jump(const FInputActionValue& InputActionValue)
{
	if (ControlledCharacter)
	{
		ControlledCharacter->Jump();
	}
}
