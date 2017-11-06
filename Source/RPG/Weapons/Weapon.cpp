// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "Weapon.h"
#include "RPG.h"
#include "Characters/RPGCharacter.h"
#include "Items/Item.h"

AWeapon::AWeapon() : Super() {
	SetType(EItemType::Weapon);
}

float AWeapon::GetChangeAmount() {
	float tempDamage = settings.healthChange * (1 + (GetGrade() * 0.25));
	tempDamage *= (1 + (GetQuality() * 0.07));
	return tempDamage; // *GetItemOwner()->GetHealthChangeModifier();
}

float AWeapon::GetRange() {
	return settings.range;
}

float AWeapon::GetDPS()
{
	return GetChangeAmount() * (1 / GetAttackSpeed());
}

bool AWeapon::IsTwoHanded()
{
	return settings.twoHanded;
}

void AWeapon::SetIsTwoHanded(bool isTwoHanded)
{
	settings.twoHanded = isTwoHanded;
}

AItem* AWeapon::Copy()
{
	return CreateWeapon(GetWorld(), GetItemOwner(), settings);
}

void AWeapon::SetChangeAmount(float newVal) {
	settings.healthChange = newVal;
}

void AWeapon::SetRange(float newVal) {
	settings.range = newVal;
}

bool AWeapon::CanFire() {
	return canFire;
}

EDamageType AWeapon::GetChangeAmountType() {
	return settings.damageType;
}

AWeapon* AWeapon::CreateWeapon(UWorld* world, ARPGCharacter* inOwner, FWeaponParams inSettings) {
	if (world != nullptr) {
		AWeapon* weapon = world->SpawnActor<AWeapon>(AWeapon::StaticClass());
		weapon->SetSettings(inSettings);
		weapon->SetItemOwner(inOwner);
		return weapon;
	}
	return nullptr;
}

void AWeapon::SetItemOwner(ARPGCharacter* inOwner) {
	Super::SetItemOwner(inOwner);

	if (inOwner != nullptr) {
		//if (partclSystem != nullptr) {
		//	// TODO Attach to end of weapon
		//	partclSystem->AttachToComponent(inOwner->GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
		//	partclSystem->SetActorParameter(FName(TEXT("BeamSource")), this);
		//}

		//inOwner->OnStopFiring.AddUniqueDynamic(this, &AWeapon::StopFire);
	}
}

float AWeapon::GetProgressBarPercent() {
	return -1;
}

FString AWeapon::GetTooltipText()
{
	FString dpsString = FString::FromInt(round(GetChangeAmount() * (1 / settings.attackSpeed)));

	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EDamageType"), true);

	FString damageType = !EnumPtr ? "Invalid" : EnumPtr->GetNameStringByIndex((int32)settings.damageType);

	return GetName() + lnBreak + "DPS: " + dpsString + lnBreak + "Damage Type: " + damageType;
}

void AWeapon::Fire(ARPGCharacter* target) {
	//FHealthChange healthChange;
	float changeAmount = GetChangeAmount();

	if (IsCrit(settings.critChance)) {
		changeAmount = changeAmount * 2;
		//healthChange.crit = true;
	}

	/*healthChange.manipulator = GetItemOwner();
	healthChange.target = target;
	healthChange.weaponUsed = this;
	healthChange.damageType = settings.damageType;
	healthChange.changeAmount = changeAmount;
	healthChange.heals = settings.heals;*/

	canFire = false;

	if (OnFire.IsBound()) {
		OnFire.Broadcast();
	}
}

void AWeapon::StopFire()
{

}

float AWeapon::GetAttackSpeed()
{
	return settings.attackSpeed;
}

void AWeapon::SetAttackSpeed(float newVal) {
	settings.attackSpeed = newVal;
}

float AWeapon::GetCritChance() {
	return settings.critChance;
}

void AWeapon::SetCritChance(float newVal) {
	settings.critChance = newVal;
}

void AWeapon::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (!canFire) {
		lastTime += DeltaTime;

		if (lastTime >= settings.attackSpeed) {
			lastTime = 0;
			canFire = true;
		}
	}
}

bool AWeapon::Heals() {
	return settings.heals;
}

void AWeapon::SetHeals(bool newVal) {
	settings.heals = newVal;
}

void AWeapon::SetSettings(FWeaponParams newSettings)
{
	settings = newSettings;
}