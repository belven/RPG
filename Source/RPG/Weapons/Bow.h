// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Weapon.h"
#include "Bow.generated.h"

/**
 *
 */
UCLASS()
class RPG_API ABow : public AWeapon
{
	GENERATED_BODY()
private:

public:
	static ABow* CreateBow(class ARPGCharacter* owner, float newHealthChange, float range, float attackSpeed);
	AItem* Copy();
};
