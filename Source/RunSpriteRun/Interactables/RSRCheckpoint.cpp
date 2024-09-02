// Copyright KittenGames

#include "RSRCheckpoint.h"
#include "Paper2D/Classes/PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "RunSpriteRun/Character/RSRCharacter.h"
#include "Kismet/GameplayStatics.h"

ARSRCheckpoint::ARSRCheckpoint()
{
	PrimaryActorTick.bCanEverTick = false;

	Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>("Flipbook");
	SetRootComponent(Flipbook);

	OverlapBox = CreateDefaultSubobject<UBoxComponent>("OverlapBox");
	OverlapBox->SetupAttachment(Flipbook);
}

void ARSRCheckpoint::BeginPlay()
{
	Super::BeginPlay();

	OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &ARSRCheckpoint::OnTriggerBoxOverlap);
}

void ARSRCheckpoint::OnTriggerBoxOverlap(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if (ARSRCharacter* Character = Cast<ARSRCharacter>(OtherActor))
	{
		Flipbook->SetFlipbook(ActivatedCheckpoint);
		UGameplayStatics::PlaySoundAtLocation(this, CheckpointSound, GetActorLocation(), FRotator::ZeroRotator);
		Character->SetRespawnLocation(GetActorLocation());
	}
}

