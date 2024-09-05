// Copyright KittenGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RSRKey.generated.h"

class UPaperSpriteComponent;
class UBoxComponent;
class USoundBase;

UCLASS()
class RUNSPRITERUN_API ARSRKey : public AActor
{
	GENERATED_BODY()
	
public:	
	ARSRKey();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SceneComponent;

	UPROPERTY(EditDefaultsOnly)
	UPaperSpriteComponent* Sprite;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* OverlapBox;

	UPROPERTY(EditAnywhere)
	USoundBase* CollectedSound;

	UFUNCTION()
	void OnBoxOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
};
