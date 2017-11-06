// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterAction.h"

UCharacterAction::UCharacterAction() : Super()
{
	SetActionType(EActionType::None);
	SetDuration(1.0);
}