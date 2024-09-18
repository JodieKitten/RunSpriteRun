// Copyright KittenGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RSRCheckpoint.generated.h"

class UPaperFlipbookComponent;
class USoundWave;
class UBoxComponent;
class UPaperFlipbook;

UCLASS()
class RUNSPRITERUN_API ARSRCheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	ARSRCheckpoint();

	FVector RespawnLocation;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = Checkpoint)
	UPaperFlipbookComponent* Flipbook;

	UPROPERTY(EditAnywhere, Category = Checkpoint)
	USoundWave* CheckpointSound;

	UPROPERTY(EditAnywhere, Category = Checkpoint)
	UBoxComponent* OverlapBox;

	UPROPERTY(EditAnywhere, Category = Checkpoint)
	UPaperFlipbook* ActivatedCheckpoint;

	UPROPERTY(EditAnywhere, Category = Checkpoint)
	UPaperFlipbook* IdleCheckpoint;

	UFUNCTION()
	void OnTriggerBoxOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
};
