// Copyright SH44N96

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Put New #includes Above

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	//Called by the Engine when Actor Damage is Dealt
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// Sets default values for this pawn's properties
	ATank();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth = StartingHealth;
};
