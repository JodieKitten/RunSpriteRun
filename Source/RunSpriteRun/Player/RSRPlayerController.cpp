// Copyright KittenGames

#include "RSRPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "RunSpriteRun/Character/RSRCharacter.h"
#include "RunSpriteRun/UI/RSRHUD.h"
#include "RunSpriteRun/UI/PauseScreenWidget.h"
#include "RunSpriteRun/UI/TimerWidget.h"
#include "Kismet/GameplayStatics.h"
#include "RunSpriteRun/RSRGameInstance.h"

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
	HUD = Cast<ARSRHUD>(GetHUD());

	OnGameStart();
}

void ARSRPlayerController::OnGameStart()
{
	if (HUD)
	{
		HUD->AddGameStartOverlay();
	}

	PauseMovement(true);

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ARSRPlayerController::StartGameTimer, 3.0f, false);
}

void ARSRPlayerController::StartGameTimer()
{
	PauseMovement(false);

	if (!TimerWidgetClass) return;
	if (!TimerWidget)
	{
		TimerWidget = CreateWidget<UTimerWidget>(this, TimerWidgetClass);
	}

	TimerWidget->bTimerActive = true;
	TimerWidget->AddToViewport();
}

void ARSRPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveLeftAction, ETriggerEvent::Triggered, this, &ARSRPlayerController::MoveLeft);
	EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &ARSRPlayerController::MoveRight);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ARSRPlayerController::Jump);
	EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &ARSRPlayerController::PauseGame);
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
		ControlledCharacter->Move(FVector(1.0f, 0.0f, 0.0f), false);
	}
}

void ARSRPlayerController::Jump(const FInputActionValue& InputActionValue)
{
	if (ControlledCharacter)
	{
		ControlledCharacter->Jump();
	}
}

void ARSRPlayerController::PauseGame(const FInputActionValue& InputActionValue)
{
	if (!PauseScreenWidgetClass) return;
	if (!PauseScreenWidget)
	{
		PauseScreenWidget = CreateWidget<UPauseScreenWidget>(this, PauseScreenWidgetClass);		
	}

	PauseScreenWidget->AddToViewport();

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(true);
	SetInputMode(InputModeData);

	bShowMouseCursor = true;

	UGameplayStatics::SetGamePaused(this, true);
}

void ARSRPlayerController::PauseMovement(bool bShouldPause)
{
	bShouldPause ? DisableInput(this) : EnableInput(this);	
}

void ARSRPlayerController::OnGameWon()
{
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(true);
	SetInputMode(InputModeData);

	bShowMouseCursor = true;
	PauseMovement(true);

	if (TimerWidget)
	{
		TimerWidget->bTimerActive = false;
	}
}
