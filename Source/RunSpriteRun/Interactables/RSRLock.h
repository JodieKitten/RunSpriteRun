// Copyright KittenGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RSRLock.generated.h"

class UPaperSpriteComponent;
class UPaperSprite;
class UBoxComponent;
class USoundBase;
class ARSRGem;
class ARSRCharacter;

UCLASS()
class RUNSPRITERUN_API ARSRLock : public AActor
{
	GENERATED_BODY()
	
public:	
	ARSRLock();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	ARSRGem* FinalGem;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SceneComponent;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* FinalGemSpawnPoint;

	UPROPERTY(EditDefaultsOnly)
	UPaperSpriteComponent* Sprite;

	UPROPERTY(EditDefaultsOnly)
	UPaperSprite* UnlockedSprite;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* OverlapBox;

	UPROPERTY(EditAnywhere)
	USoundBase* UnlockSound;

	UPROPERTY(EditAnywhere)
	USoundBase* VictorySound;

	UFUNCTION()
	void OnBoxOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	TSubclassOf<ARSRGem> Gem;

	ARSRCharacter* Character;
};
