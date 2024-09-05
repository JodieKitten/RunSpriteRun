// Copyright KittenGames


#include "RSRProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Paper2D/Classes/PaperFlipbookComponent.h"
#include "Components/SphereComponent.h"
#include "RunSpriteRun/Character/RSRCharacter.h"

ARSRProjectile::ARSRProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->InitialSpeed = 500.0f;
	ProjectileMovementComponent->MaxSpeed = 500.0f;
	ProjectileMovementComponent->Velocity.X = 1.0f;

	// Manually set a scene component so we can rotate the flipbook as needed
	SceneComponent = CreateDefaultSubobject<USceneComponent>("DefaultSceneComponent");
	SetRootComponent(SceneComponent);

	Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>("Flipbook");
	Flipbook->SetupAttachment(SceneComponent);
	Flipbook->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);


	Sphere = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	Sphere->SetupAttachment(Flipbook);
}

void ARSRProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(Lifespan);

	if(!Sphere->OnComponentBeginOverlap.IsBound())
	{ 	
		Sphere->OnComponentBeginOverlap.AddDynamic(this, &ARSRProjectile::OnSphereOverlap);
	}

}

void ARSRProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	IDamageInterface::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

