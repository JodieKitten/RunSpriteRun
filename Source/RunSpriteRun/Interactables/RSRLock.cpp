// Copyright KittenGames


#include "RSRLock.h"
#include "Paper2D/Classes/PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "RunSpriteRun/Character/RSRCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "RSRGem.h"
#include "Components/ArrowComponent.h"
#include "RunSpriteRun/UI/RSRHUD.h"
#include "RunSpriteRun/Player/RSRPlayerController.h"

ARSRLock::ARSRLock()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite");
	Sprite->SetupAttachment(RootComponent);
	Sprite->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	OverlapBox = CreateDefaultSubobject<UBoxComponent>("OverlapBox");
	OverlapBox->SetupAttachment(Sprite);

	FinalGemSpawnPoint = CreateDefaultSubobject<USceneComponent>("FinalGemSpawnPoint");
}

void ARSRLock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Character && Character->bHasKey)
	{
		if (FinalGem)
		{
			FinalGem->Destroy();
		}
	}
}

void ARSRLock::BeginPlay()
{
	Super::BeginPlay();
	
	Character = Cast<ARSRCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &ARSRLock::OnBoxOverlap);
}

void ARSRLock::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if (Character == OtherActor)
	{
		ARSRPlayerController* Controller = Cast<ARSRPlayerController>(Character->GetController());
		ARSRHUD* HUD = Cast<ARSRHUD>(Controller->GetHUD());

		if (Character->bHasKey)
		{
			UGameplayStatics::SpawnSoundAtLocation(this, UnlockSound, GetActorLocation(), FRotator::ZeroRotator);
			UGameplayStatics::SpawnSoundAtLocation(this, VictorySound, GetActorLocation(), FRotator::ZeroRotator);
			Sprite->SetSprite(UnlockedSprite);
			SetActorEnableCollision(false);
			Character->bHasKey = false;

			HUD->AddWinScreenOverlay();
			Controller->OnGameWon();
		}
		else
		{
			FActorSpawnParameters Params;
			FinalGem = GetWorld()->SpawnActor<ARSRGem>(Gem, FinalGemSpawnPoint->GetComponentTransform(), Params);
			if (FinalGem)
			{
				FinalGem->Waypoint->SetRelativeLocation(Character->StartingLocation);
			}

			HUD->AddKeyNeededOverlay();
		}
	}
}


