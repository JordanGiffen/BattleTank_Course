// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    auto ControlledTank = GetControlledTank();
    if (!ControlledTank) { UE_LOG(LogTemp, Error, TEXT("No tank reference found in ATankAIController!")); }
    else { UE_LOG(LogTemp, Warning, TEXT("AI Tank Controller %s is controlling Tank %s."), *GetName(), *ControlledTank->GetName()); }

    auto PlayerTank = GetPlayerTank();
    if (!PlayerTank) { UE_LOG(LogTemp, Error, TEXT("No player tank reference found in ATankAIController!")); }
    else { UE_LOG(LogTemp, Warning, TEXT("AI Tank Controller %s found player Tank %s."), *GetName(), *PlayerTank->GetName()); }
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (GetPlayerTank())
    {
        // TODO move towards the player

        // Aim towards the player
        GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

        // Fire if ready
        
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