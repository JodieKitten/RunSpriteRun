// Copyright KittenGames


#include "MainMenuGameModeBase.h"
#include "RunSpriteRun/Player/RSRPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "RunSpriteRun/UI/MainMenuWidget.h"

void AMainMenuGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(true);
	Controller->SetInputMode(InputModeData);

	Controller->bShowMouseCursor = true;

	if (!MainMenuWidgetClass) return;
	if (!MainMenuWidget)
	{
		MainMenuWidget = CreateWidget<UMainMenuWidget>(Controller, MainMenuWidgetClass);
	}

	MainMenuWidget->AddToViewport();
}
