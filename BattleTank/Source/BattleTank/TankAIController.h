// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

// Forward declarations
class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnPossessedTankDeath();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

	virtual void SetPawn(APawn* InPawn) override;

	// How close the AI tank can get to the player (in centimeters)
	float AcceptanceRadius = 8000.f;

	
};
