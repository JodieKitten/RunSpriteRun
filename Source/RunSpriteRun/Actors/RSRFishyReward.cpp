// Copyright KittenGames

#include "RSRFishyReward.h"
#include "RunSpriteRun/Character/RSRCharacter.h"
#include "Paper2D/Classes/PaperSpriteComponent.h"
#include "Components/BoxComponent.h"

ARSRFishyReward::ARSRFishyReward()
{
	PrimaryActorTick.bCanEverTick = true;

	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite");
	Sprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	OverlapBox = CreateDefaultSubobject<UBoxComponent>("OverlapBox");
	OverlapBox->SetupAttachment(Sprite);
}

void ARSRFishyReward::BeginPlay()
{
	Super::BeginPlay();

	FScriptDelegate Delegate;
	Delegate.BindUFunction(this, "OnBoxEndOverlap");
	OverlapBox->OnComponentEndOverlap.AddUnique(Delegate);

}

float ARSRFishyReward::TransformedSin()
{
	return Amplitude * FMath::Sin(RunningTime * TimeConstant);
}

void ARSRFishyReward::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ARSRCharacter* Character = Cast<ARSRCharacter>(OtherActor))
	{
		// So the player can't run back the way they came but can enjoy movement on game end
		OverlapBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	}
}

void ARSRFishyReward::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RunningTime += DeltaTime;

	// Makes the fishy bob
	AddActorWorldOffset(FVector(0.f, 0.f, TransformedSin()));
}

