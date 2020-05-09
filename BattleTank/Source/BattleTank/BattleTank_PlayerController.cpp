// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank_PlayerController.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

void ABattleTank_PlayerController::BeginPlay()
{
    Super::BeginPlay();

    auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
    if (AimingComponent)
    {
        FoundAimingComponent(AimingComponent);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Player controller can't find aiming component at Begin Play"))
    }
    
    
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
        GetControlledTank()->AimAt(HitLocation);
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
    FVector TraceEndLocation = TraceStartLocation + LookDirection * LineTraceRange;
    FCollisionQueryParams CollisionQueryParams{FName(""), false, GetPawn()};
    FCollisionResponseParams CollisionResponseParams;
    if (GetWorld()->LineTraceSingleByChannel
    (
        HitResult,
        TraceStartLocation,
        TraceEndLocation,
        ECollisionChannel::ECC_Visibility,
        CollisionQueryParams)
    )
    {
        OutHitLocation = HitResult.Location;
        return true;
    }
    OutHitLocation = FVector(0.f, 0.f, 0.f);
    return false;
}