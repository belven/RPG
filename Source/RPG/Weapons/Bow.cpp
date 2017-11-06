// Fill out your copyright notice in the Description page of Project Settings.

#include "Bow.h"
#include "Characters/RPGCharacter.h"

ABow* ABow::CreateBow(class ARPGCharacter* owner, float newHealthChange, float range, float attackSpeed)
{
	ABow* bow = owner->GetWorld()->SpawnActor<ABow>(StaticClass());
	bow->SetRange(range);
	bow->SetChangeAmount(newHealthChange);
	bow->SetAttackSpeed(attackSpeed);
	bow->SetItemOwner(owner);
	return bow;
}

AItem* ABow::Copy()
{
	ABow* weapon = GetWorld()->SpawnActor<ABow>(StaticClass());
	weapon->SetSettings(settings);
	return weapon;
}