// Copyright KittenGames


#include "RSRGem.h"
#include "Paper2D/Classes/PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "RunSpriteRun/Character/RSRCharacter.h"
#include "Kismet/GameplayStatics.h"

ARSRGem::ARSRGem()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>("Flipbook");
	Flipbook->SetupAttachment(RootComponent);

	OverlapBox = CreateDefaultSubobject<UBoxComponent>("OverlapBox");
	OverlapBox->SetupAttachment(Flipbook);

	Waypoint = CreateDefaultSubobject<UArrowComponent>("Waypoint");
	Waypoint->SetupAttachment(RootComponent);
}

void ARSRGem::BeginPlay()
{
	Super::BeginPlay();

	OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &ARSRGem::OnBoxOverlap);
	
}

void ARSRGem::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if (ARSRCharacter* Character = Cast<ARSRCharacter>(OtherActor))
	{
		if (ActorHasTag("FinalGem"))
		{
			Waypoint->SetWorldLocation(Character->StartingLocation);
		}

		FVector DestinationLocation = Waypoint->GetComponentLocation();
		FRotator DestinationRotation = Waypoint->GetComponentRotation();

		Character->EnableCameraLag(false);
		Character->TeleportTo(DestinationLocation, DestinationRotation);
		UGameplayStatics::PlaySoundAtLocation(this, WarpSound, GetActorLocation(), FRotator::ZeroRotator);
	}
}
