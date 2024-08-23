// Copyright KittenGames

#include "RSRCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"

ARSRCharacter::ARSRCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 200.0f;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
	Camera->SetProjectionMode(ECameraProjectionMode::Perspective);
	Camera->SetFieldOfView(90.0f);
}

void ARSRCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(GetSprite()))
	{
		GetSprite()->SetFlipbook(IdleFlipbook);
	}
}

void ARSRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
