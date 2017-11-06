// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicAIController.h"
#include "CollisionQueryParams.h"
#include "WorldCollision.h"

ABasicAIController::ABasicAIController() : Super()
{
}

bool ABasicAIController::IsInWeaponRange(float range, AActor* other)
{
	float dist = FVector::Distance(GetPawn()->GetActorLocation(), other->GetActorLocation());
	return dist <= range;
}

TArray<FHitResult> ABasicAIController::GetActorsInRadius(float radius)
{
	TArray<FHitResult> OutHits;
	FVector endLocation = GetPawn()->GetActorLocation();
	endLocation.Z = 15;

	FCollisionObjectQueryParams objectParams;
	objectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);

	FCollisionQueryParams params;
	//params.

	GetWorld()->SweepMultiByObjectType(OutHits, GetPawn()->GetActorLocation(), endLocation, FQuat(), objectParams, FCollisionShape::MakeSphere(radius), params);

	return OutHits;
}
