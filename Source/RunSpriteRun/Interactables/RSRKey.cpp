// Copyright KittenGames


#include "RSRKey.h"
#include "Paper2D/Classes/PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "RunSpriteRun/Character/RSRCharacter.h"
#include "Kismet/GameplayStatics.h"

ARSRKey::ARSRKey()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite");
	Sprite->SetupAttachment(RootComponent);
	Sprite->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	OverlapBox = CreateDefaultSubobject<UBoxComponent>("OverlapBox");
	OverlapBox->SetupAttachment(Sprite);
}

void ARSRKey::BeginPlay()
{
	Super::BeginPlay();
	
	OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &ARSRKey::OnBoxOverlap);
}

void ARSRKey::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (ARSRCharacter* Character = Cast<ARSRCharacter>(OtherActor))
	{
		Character->bHasKey = true;
		UGameplayStatics::PlaySoundAtLocation(this, CollectedSound, GetActorLocation(), FRotator::ZeroRotator);
		Sprite->SetVisibility(false);
		SetActorEnableCollision(false);
	}
}
