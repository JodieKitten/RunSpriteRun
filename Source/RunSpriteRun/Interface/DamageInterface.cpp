// Copyright KittenGames

#include "DamageInterface.h"
#include "RunSpriteRun/Character/RSRCharacter.h"

// Add default functionality here for any IDamageInterface functions that are not pure virtual.

void IDamageInterface::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex,
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if (ARSRCharacter* Character = Cast<ARSRCharacter>(OtherActor))
	{
		Character->Die();
		//OverlappedComponent->GetOwner()->Destroy();
	}

}
