// Copyright SH44N96

#include "TankAIController.h"
#include "Tank.h" // So we can implement OnDeath
#include "TankAimingComponent.h"

// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    auto ControlledTank = GetPawn();

    if(!(PlayerTank && ControlledTank)) { return; }

    // Move towards the player
    MoveToActor(PlayerTank, AcceptanceRadius); // TODO Check radius is in cm

    // Aim towards the player
    auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
    AimingComponent->AimAt(PlayerTank->GetActorLocation());

    if(AimingComponent->GetFiringState() == EFiringState::Locked)
    {
        AimingComponent->Fire(); // TODO Limit firing rate
    }
}

void ATankAIController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);
    if(InPawn)
    {
        auto PossessedTank = Cast<ATank>(InPawn);
        if(!(PossessedTank)) { return; }

        // Subscribe our local method to the tank's death event
        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
    }
}

void ATankAIController::OnPossessedTankDeath()
{
    if(!ensure(GetPawn())) { return; } // TODO Remove if ok
    GetPawn()->DetachFromControllerPendingDestroy();
}
