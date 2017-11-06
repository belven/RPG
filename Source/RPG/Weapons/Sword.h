// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Weapon.h"
#include "Sword.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API ASword : public AWeapon
{
	GENERATED_BODY()
	
public:
	ASword();
	static ASword* CreateSword(class ARPGCharacter* owner, float newHealthChange, float range, float attackSpeed);
	
	
		virtual AItem* Copy();
};
