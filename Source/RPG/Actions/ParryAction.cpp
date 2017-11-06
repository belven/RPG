// Fill out your copyright notice in the Description page of Project Settings.

#include "ParryAction.h"

UParryAction::UParryAction() : Super()
{
	SetActionType(EActionType::Parry);
	SetCanCancel(false);
}

UParryAction* UParryAction::CreateParryAction()
{
	UParryAction* action = NewObject<UParryAction>(StaticClass());
	return action;
}
