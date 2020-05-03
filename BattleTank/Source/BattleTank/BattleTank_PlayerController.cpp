// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
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
        // UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
        // TODO tell controlled tank to aim at this point
    }
    
}

bool ABattleTank_PlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
    // Find the crosshair position in pixel coordinates
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

    
    // "De-project" the screen position of the crosshair to the world direction
    FVector CameraWorldLocation; // To be discarded (Could be used instead of GetCameraLocation)
    FVector LookDirection;
    if (GetLookDirection(ScreenLocation, LookDirection, CameraWorldLocation))
    {
        // Line-trace along that look direction, and see what we hit (up to max range)
        GetLookVectorHitLocation(LookDirection, OutHitLocation);
    }

    UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *OutHitLocation.ToString());

    return true;
}

bool ABattleTank_PlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection, FVector& CameraWorldLocation) const
{
    return DeprojectScreenPositionToWorld
    (
    ScreenLocation.X,
    ScreenLocation.Y,
    CameraWorldLocation,
    LookDirection
    );
}

bool ABattleTank_PlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
    FHitResult HitResult;
    FVector TraceStartLocation = PlayerCameraManager->GetCameraLocation();
    FCollisionQueryParams CollisionQueryParams{FName(""), false, GetPawn()};
    FCollisionResponseParams CollisionResponseParams;
    if (GetWorld()->LineTraceSingleByChannel
    (
        HitResult,
        TraceStartLocation,
        LookDirection * LineTraceRange,
        ECC_Visibility,
        CollisionQueryParams,
        CollisionResponseParams
    )
    )
    {
        OutHitLocation = HitResult.Location;
        return true;
    }
    return false;
}