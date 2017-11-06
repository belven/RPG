// Fill out your copyright notice in the Description page of Project Settings.

#include "Sword.h"
#include "Characters/RPGCharacter.h"
#include "ConstructorHelpers.h"
#include "Engine/StaticMesh.h"

ASword::ASword() : Super()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> smg(TEXT("/Game/FirstPerson/Sword/Sword"));
	if (smg.Succeeded())
	{
		SetMesh(smg.Object);
	}
	GetMeshComponent()->SetStaticMesh(GetMesh());
}

ASword* ASword::CreateSword(class ARPGCharacter* owner, float newHealthChange, float range, float attackSpeed)
{
	ASword* sword = owner->GetWorld()->SpawnActor<ASword>(StaticClass());
	sword->SetRange(range);
	sword->SetChangeAmount(newHealthChange);
	sword->SetAttackSpeed(attackSpeed);
	sword->SetItemOwner(owner);

	return sword;
}

AItem* ASword::Copy()
{
	ASword* weapon = GetWorld()->SpawnActor<ASword>(StaticClass());
	weapon->SetSettings(settings);
	return weapon;
}