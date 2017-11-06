// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/CharacterAction.h"
#include "DodgeAction.generated.h"

/**
 *
 */
UCLASS()
class RPG_API UDodgeAction : public UCharacterAction
{
	GENERATED_BODY()

public:
		UDodgeAction();

	UFUNCTION(BlueprintCallable, Category = "Action")
		static UDodgeAction* CreateDodgeAction();

};
