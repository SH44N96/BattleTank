// Copyright SH44N96

#include "TankAIController.h"
#include "TankAimingComponent.h"

// Depends on Movement Component via Pathfinding System

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    auto ControlledTank = GetPawn();

    if(!ensure(PlayerTank && ControlledTank)) { return; }

    // Move Towards the Player
    MoveToActor(PlayerTank, AcceptanceRadius); // TODO: Check Radius is in cm

    // Aim Towards the Player
    auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
    AimingComponent->AimAt(PlayerTank->GetActorLocation());

    if(AimingComponent->GetFiringState() == EFiringState::Locked)
    {
        AimingComponent->Fire(); // TODO: Limit Firing Rate
    }
}
