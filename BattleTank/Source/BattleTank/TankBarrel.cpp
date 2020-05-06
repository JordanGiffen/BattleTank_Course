// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);
    auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
    auto Elevation = FMath::Clamp<float>(RawNewElevation, MinDegreesElevation, MaxDegreesElevation);
    SetRelativeRotation(FRotator(Elevation, 0, 0));
}