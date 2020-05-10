// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/Controller.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"
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
    auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

    if (!ensure(PlayerTank && ControlledTank)) { return; }
    // Move towards the player
    MoveToActor(PlayerTank, AcceptanceRadius);

    // Aim towards the player
    AimingComponent->AimAt(PlayerTank->GetActorLocation());

    AimingComponent->Fire(); // TODO Limit firing rate
}