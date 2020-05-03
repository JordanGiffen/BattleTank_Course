// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank_PlayerController.h"

void ABattleTank_PlayerController::BeginPlay()
{
    Super::BeginPlay();

    auto ControlledTank = GetControlledTank();
    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Error, TEXT("No tank reference found in BattleTank_PlayerController!"));
    }
    UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *ControlledTank->GetName());
}

void ABattleTank_PlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    AimTowardsCrosshair();
}

ATank* ABattleTank_PlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ABattleTank_PlayerController::AimTowardsCrosshair()
{
    if (!GetControlledTank()) { return; }

    FVector HitLocation; // used as an Out parameter

    if (GetSightRayHitLocation(HitLocation)) // HitLocation will be set by function (OUT parameter)
    {
        UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
        // TODO tell controlled tank to aim at this point
    }
    
}

bool ABattleTank_PlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
    // Get world location through crosshair linetrace
    // If it hits the landscape
        // Tell controlled tank to aim at this point
    return false;
}