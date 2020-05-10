// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::TankTrack()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    UE_LOG(LogTemp, Warning, TEXT("Track ticking"))
}

void UTankTrack::SetThrottle(float Throttle)
{
    // TODO clamp actual throttle value to prevent cheating
    auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}