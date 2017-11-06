// Fill out your copyright notice in the Description page of Project Settings.

#include "BlockAction.h"

UBlockAction::UBlockAction() : Super()
{
	SetActionType(EActionType::Block);
	SetCanCancel(true);
}

UBlockAction* UBlockAction::CreateBlockAction()
{
	UBlockAction* action = NewObject<UBlockAction>(StaticClass());
	return action;
}
