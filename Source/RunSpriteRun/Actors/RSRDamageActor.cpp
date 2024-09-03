// Copyright KittenGames


#include "RSRDamageActor.h"
#include "Paper2D/Classes/PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"

ARSRDamageActor::ARSRDamageActor()
{
	PrimaryActorTick.bCanEverTick = false;

	// Manually set a scene component so we can rotate the flipbook as needed
	SceneComponent = CreateDefaultSubobject<USceneComponent>("DefaultSceneComponent");
	SetRootComponent(SceneComponent);

	Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>("Flipbook");
	Flipbook->SetupAttachment(SceneComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(Flipbook);
}

void ARSRDamageActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (!BoxComponent->OnComponentBeginOverlap.IsBound())
	{
		BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ARSRDamageActor::OnSphereOverlap);
	}
}

void ARSRDamageActor::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	IDamageInterface::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}
