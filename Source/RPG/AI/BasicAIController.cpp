// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicAIController.h"
#include "Characters/RPGCharacter.h"
#include "CollisionQueryParams.h"
#include "WorldCollision.h"

ABasicAIController::ABasicAIController() : Super()
{}

bool ABasicAIController::IsInWeaponRange(float range, AActor* other)
{
	float dist = FVector::Distance(GetPawn()->GetActorLocation(), other->GetActorLocation());
	return dist <= range;
}

EActionType ABasicAIController::CalculateNextAction(ARPGCharacter* target)
{
	EActionType action = EActionType::None;

	if (target->IsPerformingAction(EActionType::Attack))
	{
		ARPGCharacter* ownedCharacter = GetRPGCharacter();

		if (ownedCharacter->CanParry()
			&& ownedCharacter->CanPerformAction(EActionType::Parry))
		{
			action = EActionType::Parry;
		}
		else if (ownedCharacter->CanBlock()
			&& ownedCharacter->CanPerformAction(EActionType::Block))
		{
			action = EActionType::Block;
		}
		else
		{
			action = EActionType::Dodge;
		}
	}
	else if (target->IsPerformingAction(EActionType::Stagger) || target->IsPerformingAction(EActionType::None))
	{
		action = EActionType::Attack;
	}
	
	return action;
}

ARPGCharacter* ABasicAIController::GetRPGCharacter()
{
	return Cast<ARPGCharacter>(GetPawn());
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
