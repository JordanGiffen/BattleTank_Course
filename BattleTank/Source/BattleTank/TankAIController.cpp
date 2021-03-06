// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/Controller.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "Tank.h" // So we can implement OnDeath
// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);
    if (InPawn)
    {
        auto PossessedTank = Cast<ATank>(InPawn);
        if (!ensure(PossessedTank)) { return; }

        // Subscribe our local method to the tanks death event
        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
    }
}

void ATankAIController::OnPossessedTankDeath()
{
    if (!GetPawn()) { return; }
    GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);


    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    auto ControlledTank = GetPawn();
    auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
    
    if (!ensure(PlayerTank && ControlledTank)) { return; }
    // Move towards the player
    MoveToActor(PlayerTank, AcceptanceRadius);

    // Aim towards the player
    AimingComponent->AimAt(PlayerTank->GetActorLocation());

    if (AimingComponent->GetFiringState() == EFiringState::Locked)
    {
        AimingComponent->Fire(); // TODO Limit firing rate
    }
}