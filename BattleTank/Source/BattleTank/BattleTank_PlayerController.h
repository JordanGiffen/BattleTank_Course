// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BattleTank_PlayerController.generated.h"

// Forward declarations
class UTankAimingComponent;

/**
 * Responsible for helping the aim.
 */
UCLASS()
class BATTLETANK_API ABattleTank_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimingCompRef);

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Start the tank moving the barrel so that a shot would hit where
	// the crosshair intersects with the world
	void AimTowardsCrosshair();

	// Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = .5f;
	
	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = .33333f;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection, FVector& CameraWorldLocation) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.f;

	UTankAimingComponent* AimingComponent = nullptr;
};
