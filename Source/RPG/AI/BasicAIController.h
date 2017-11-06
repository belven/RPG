// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BasicAIController.generated.h"

/**
 *
 */
UCLASS()
class RPG_API ABasicAIController : public AAIController
{
	GENERATED_BODY()
public:
	ABasicAIController();

	UFUNCTION(BlueprintCallable, Category = "Widgets")
		bool IsInWeaponRange(float range, AActor* other);

	UFUNCTION(BlueprintCallable, Category = "Trace")
		TArray<FHitResult> GetActorsInRadius(float radius);
};
