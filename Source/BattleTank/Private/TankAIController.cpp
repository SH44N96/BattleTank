// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    auto PlayerTank = GetPlayerTank();
    if(!PlayerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController can't find PlayerTank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController found PlayerTank: %s"), *(PlayerTank->GetName()));
    }
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
    auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    return Cast<ATank>(PlayerPawn);
}