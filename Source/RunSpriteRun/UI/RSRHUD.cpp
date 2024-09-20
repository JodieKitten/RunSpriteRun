// Copyright KittenGames


#include "RSRHUD.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "WinScreenWidget.h"

void ARSRHUD::AddGameStartOverlay()
{
	CreateWidgetAndAddToViewport(GameStartWidget, GameStartClass, true, 3.0f);
}

void ARSRHUD::AddTimerOverlay()
{
	CreateWidgetAndAddToViewport(TimerWidget, TimerWidgetClass, false);
}

void ARSRHUD::AddKeyFoundOverlay()
{
	CreateWidgetAndAddToViewport(KeyFoundWidget, KeyFoundClass, true, 5.0f);
}

void ARSRHUD::AddKeyNeededOverlay()
{
	CreateWidgetAndAddToViewport(KeyNeededWidget, KeyNeededClass, true, 5.0f);
}

void ARSRHUD::AddWinScreenOverlay()
{
	CreateWidgetAndAddToViewport(WinScreenWidget, WinScreenClass, false);
}

void ARSRHUD::CreateWidgetAndAddToViewport(UUserWidget* Widget, TSubclassOf<UUserWidget> WidgetClass, bool bRemove, float Duration)
{
	APlayerController* PlayerController = GetOwningPlayerController();
	if (WidgetClass)
	{
		Widget = CreateWidget<UUserWidget>(PlayerController, WidgetClass);
		if (Widget)
		{
			Widget->AddToViewport();
		}
	}

	if (bRemove)
	{
		FTimerHandle TimerHandle;
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUFunction(this, FName("RemoveWidgetFromParent"), Widget);
		GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, Duration, false);
	}
}

void ARSRHUD::RemoveWidgetFromParent(UUserWidget* WidgetToRemove)
{
	WidgetToRemove->RemoveFromParent();
}
