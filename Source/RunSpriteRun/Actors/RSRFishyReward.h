// Copyright KittenGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RSRFishyReward.generated.h"

class UPaperSpriteComponent;
class UBoxComponent;

UCLASS()
class RUNSPRITERUN_API ARSRFishyReward : public AActor
{
	GENERATED_BODY()
	
public:	
	ARSRFishyReward();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	UPaperSpriteComponent* Sprite;

	UPROPERTY(EditAnywhere)
	UBoxComponent* OverlapBox;

	float TransformedSin();

	UPROPERTY(EditAnywhere)
	float Amplitude = 0.25f;
	
	UPROPERTY(EditAnywhere)
	float TimeConstant = 5.0f;

	UPROPERTY(EditAnywhere)
	float RunningTime;

	UFUNCTION()
	void OnBoxEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
};
