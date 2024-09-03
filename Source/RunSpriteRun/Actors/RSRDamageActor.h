// Copyright KittenGames

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RunSpriteRun/Interface/DamageInterface.h"
#include "RSRDamageActor.generated.h"


class UPaperFlipbookComponent;
class UBoxComponent;

UCLASS()
class RUNSPRITERUN_API ARSRDamageActor : public AActor, public IDamageInterface
{
	GENERATED_BODY()

	
public:	
	ARSRDamageActor();

	UFUNCTION()
	void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SceneComponent;

	UPROPERTY(EditDefaultsOnly)
	UPaperFlipbookComponent* Flipbook;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxComponent;

};
