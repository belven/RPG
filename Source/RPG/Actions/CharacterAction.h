// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "UObject/NoExportTypes.h"
#include "CharacterAction.generated.h"

UCLASS()
class RPG_API UCharacterAction : public UObject
{
	GENERATED_BODY()

protected:
	EActionType actionType;
	bool canCancel;
	float duration;
public:
		UCharacterAction();

	UFUNCTION(BlueprintCallable, Category = "Action")
		EActionType GetActionType() { return actionType; }

	UFUNCTION(BlueprintCallable, Category = "Action")
		void SetActionType(EActionType val) { actionType = val; }
	
	UFUNCTION(BlueprintCallable, Category = "Action")
		bool CanBeCancelled() { return canCancel; }

	UFUNCTION(BlueprintCallable, Category = "Action")
		void SetCanCancel(bool val) { canCancel = val; }

	UFUNCTION(BlueprintCallable, Category = "Action")
		float GetDuration() { return duration; }

	UFUNCTION(BlueprintCallable, Category = "Action")
		void SetDuration(float val) { duration = val; }
};
