// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    auto ControlledTank = GetControlledTank();
    if(!ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController not Possessing a Tank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController Possessing: %s"), *(ControlledTank->GetName()));
    }
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if(!GetControlledTank())
    {
        return;
    }

    FVector HitLocation; // OUT Parameter
    if(GetSightRayHitLocation(HitLocation)) // Has "side-effect", is going to line-trace
    {
    // UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *HitLocation.ToString());
    // TODO: Tell controlled tank to aim at this point
    }
}

// Get world location of line-trace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
    // Find the crosshair position in pixel coordinates
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

    // "De-project" the screen position of the crosshair to a world direction
    FVector LookDirection;
    if(GetLookDirection(ScreenLocation, LookDirection))
    {
        UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *LookDirection.ToString());
    }

    // Line-trace along that LookDirection, and see what we hit (up to max. range)
    return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWorldLocation; // To be discarded

    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}
