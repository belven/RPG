// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/CharacterAction.h"
#include "StaggerAction.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UStaggerAction : public UCharacterAction
{
	GENERATED_BODY()
public:
	UStaggerAction();

	UFUNCTION(BlueprintCallable, Category = "Action")
		static UStaggerAction* CreateStaggerAction();
	
	
	
};
