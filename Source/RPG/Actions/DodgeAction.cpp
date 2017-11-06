// Fill out your copyright notice in the Description page of Project Settings.

#include "DodgeAction.h"

UDodgeAction::UDodgeAction() : Super()
{
	SetActionType(EActionType::Dodge);
	SetCanCancel(false);
}

UDodgeAction* UDodgeAction::CreateDodgeAction()
{
	UDodgeAction* action = NewObject<UDodgeAction>(StaticClass());
	return action;
}