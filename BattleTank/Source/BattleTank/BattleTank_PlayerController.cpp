// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank_PlayerController.h"

void ABattleTank_PlayerController::BeginPlay()
{
    Super::BeginPlay();
    if (!GetControlledTank())
    {
        UE_LOG(LogTemp, Error, TEXT("No tank reference found in BattleTank_PlayerController!"));
    }
    UE_LOG(LogTemp, Warning, TEXT("Tank being possessed: %s"), *GetControlledTank()->GetName());
}

ATank* ABattleTank_PlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ABattleTank_PlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
}