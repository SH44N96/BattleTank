// Copyright SH44N96

#include "TankPlayerController.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if(!ensure(AimingComponent)) { return; }

    FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if(!GetPawn()) { return; } // e.g. if Not Possessing

    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if(!ensure(AimingComponent)) { return; }

    FVector HitLocation; // OUT Parameter
    bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
    if(bGotHitLocation) // Has "Side-Effect", is Going to Line-Trace
    {
        AimingComponent->AimAt(HitLocation);
    }
}

// Get World Location of Line-Trace through Crosshair, True if Hits Landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
    // Find the Crosshair Position in Pixel Coordinates
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

    // "De-Project" the Screen Position of the Crosshair to a World Direction
    FVector LookDirection;
    if(GetLookDirection(ScreenLocation, LookDirection))
    {
        // Line-Trace along that LookDirection, and See what we Hit (up to Max. Range)
        return GetLookVectorHitLocation(LookDirection, HitLocation);
    }

    return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWorldLocation; // To be Discarded

    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
    FHitResult HitResult;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

    if(GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
    {
        HitLocation = HitResult.Location;
        return true;
    }

    HitLocation = FVector(0);
    return false; // Line-Trace didn't Succeed
}
