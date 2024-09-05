// Copyright KittenGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RSRGem.generated.h"

class UPaperFlipbookComponent;
class UBoxComponent;
class UArrowComponent;
class USoundBase;

UCLASS()
class RUNSPRITERUN_API ARSRGem : public AActor
{
	GENERATED_BODY()
	
public:	
	ARSRGem();

	UPROPERTY(EditAnywhere)
	UArrowComponent* Waypoint;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SceneComponent;

	UPROPERTY(EditDefaultsOnly)
	UPaperFlipbookComponent* Flipbook;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* OverlapBox;

	UPROPERTY(EditAnywhere)
	USoundBase* WarpSound;

	UFUNCTION()
	void OnBoxOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
};
