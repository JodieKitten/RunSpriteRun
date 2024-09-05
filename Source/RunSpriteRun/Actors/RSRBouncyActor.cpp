// Copyright KittenGames


#include "RSRBouncyActor.h"
#include "Paper2D/Classes/PaperSpriteComponent.h"
#include "RunSpriteRun/Character/RSRCharacter.h"
#include "Kismet/Gameplaystatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ARSRBouncyActor::ARSRBouncyActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("DefaultSceneComponent");
	SetRootComponent(SceneComponent);

	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite");
	Sprite->SetupAttachment(RootComponent);

	OverlapBox = CreateDefaultSubobject<UBoxComponent>("OverlapBox");
	OverlapBox->SetupAttachment(Sprite);

}

void ARSRBouncyActor::BeginPlay()
{
	Super::BeginPlay();
	
	OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &ARSRBouncyActor::OnComponentOverlap);
	Character = Cast<ARSRCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
}

void ARSRBouncyActor::OnComponentOverlap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (Character == OtherActor)
	{
		Character->LaunchCharacter(FVector(LaunchVelocityX, 0.0f, LaunchVelocityZ), true, true);
		ChangeCameraView();
		UGameplayStatics::PlaySoundAtLocation(this, BoingSound, GetActorLocation());
		Sprite->SetSprite(TrampolineUp);

		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ARSRBouncyActor::ResetTrampoline, 1.0f, false);
	}
}

void ARSRBouncyActor::ChangeCameraView()
{
	if (Character)
	{	
		Character->ChangeCameraView();
	}
}

void ARSRBouncyActor::ResetTrampoline()
{
	Sprite->SetSprite(TrampolineDown);
}