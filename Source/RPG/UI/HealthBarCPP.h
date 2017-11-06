// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarCPP.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UHealthBarCPP : public UUserWidget
{
	GENERATED_BODY()
	
private:
	class ARPGCharacter* owner;

public:
	
	UFUNCTION(BlueprintCallable, Category = "Owner")
		class ARPGCharacter* GetOwner() { return owner; }

	UFUNCTION(BlueprintCallable, Category = "Owner")
		void SetOwner(class ARPGCharacter* val) { owner = val; }

	UFUNCTION(BlueprintCallable, Category = "Health")
		float GetCurrentHealth();

	UFUNCTION(BlueprintCallable, Category = "Health")
		float GetMaxHealth();
};
