// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthBarCPP.h"
#include "Characters/RPGCharacter.h"


float UHealthBarCPP::GetCurrentHealth()
{
	return owner != nullptr ? owner->GetCurrentHealth() : 0.0;
}

float UHealthBarCPP::GetMaxHealth()
{
	return owner != nullptr ? owner->GetMaxHealth() : 0.0;
}
