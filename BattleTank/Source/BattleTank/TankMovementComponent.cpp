// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
    if (!LeftTrack || !RightTrack) { return; }
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
    // TODO prevent double-speed due to dual control use
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForwardDirection = GetOwner()->GetActorForwardVector();
    auto AIForwardIntention = MoveVelocity.GetSafeNormal();

    auto ForwardThrow = FVector::DotProduct(AIForwardIntention, TankForwardDirection);

    auto RightThrow = FVector::CrossProduct(AIForwardIntention, TankForwardDirection);

    IntendTurnRight(RightThrow.Z);

    // IntendMoveForward(ForwardThrow);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
    UE_LOG(LogTemp, Warning, TEXT("%f"), Throw);
    if (!LeftTrack || !RightTrack) { return; }
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);
    // TODO prevent double-speed due to dual control use
}