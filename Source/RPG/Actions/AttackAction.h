// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/CharacterAction.h"
#include "AttackAction.generated.h"

class AWeapon;

UCLASS()
class RPG_API UAttackAction : public UCharacterAction
{
	GENERATED_BODY()
private:
	UPROPERTY()
		TMap<EWeaponPosition, AWeapon*> weaponsUsed;
	class ARPGCharacter* target;
public:
		UAttackAction();

	UFUNCTION(BlueprintCallable, Category = "Action")
		static UAttackAction* CreateAttackAction();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		TMap<EWeaponPosition, AWeapon*>& GetWeaponsUsed() { return weaponsUsed; }

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void SetWeaponsUsed(TMap<EWeaponPosition, AWeapon*> val) { weaponsUsed = val; }

	UFUNCTION(BlueprintCallable, Category = "Target")
		class ARPGCharacter* GetTarget() { return target; }

	UFUNCTION(BlueprintCallable, Category = "Target")
		void SetTarget(class ARPGCharacter* val) { target = val; }
};