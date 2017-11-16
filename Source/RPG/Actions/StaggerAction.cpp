// Fill out your copyright notice in the Description page of Project Settings.

#include "StaggerAction.h"

UStaggerAction::UStaggerAction() : Super()
{
	SetActionType(EActionType::Stagger);
	SetCanCancel(false);
}


UStaggerAction* UStaggerAction::CreateStaggerAction()
{
	UStaggerAction* action = NewObject<UStaggerAction>(StaticClass());
	return action;
}
