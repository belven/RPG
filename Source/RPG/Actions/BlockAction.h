// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/CharacterAction.h"
#include "BlockAction.generated.h"

/**
 *
 */
UCLASS()
class RPG_API UBlockAction : public UCharacterAction
{
	GENERATED_BODY()

public:
		UBlockAction();

	UFUNCTION(BlueprintCallable, Category = "Action")
		static UBlockAction* CreateBlockAction();
};