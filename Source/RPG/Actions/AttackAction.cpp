// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackAction.h"
#include "Characters/RPGCharacter.h"
#include "Weapons/Weapon.h"

UAttackAction::UAttackAction() : Super()
{
	SetActionType(EActionType::Attack);
	SetCanCancel(false);
}

UAttackAction* UAttackAction::CreateAttackAction()
{
	UAttackAction* action = NewObject<UAttackAction>(StaticClass());
	return action;
}