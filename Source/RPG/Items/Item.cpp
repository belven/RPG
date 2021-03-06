///////////////////////////////////////////////////////////
//  AItem.cpp
//  Implementation of the Class AItem
//  Created on:      04-May-2015 11:16:11
//  Original author: sam
///////////////////////////////////////////////////////////
#include "Item.h"
#include "RPG.h"
#include "Characters/RPGCharacter.h"

int32 AItem::HighestItemLevel = 100;

void AItem::CloneItemSettings(AItem* cloneFromItem)
{
	SetName(cloneFromItem->GetName());
	SetGrade(cloneFromItem->GetGrade());
	SetQuality(cloneFromItem->GetQuality());
	SetType(cloneFromItem->GetType());
	SetItemOwner(cloneFromItem->GetItemOwner());
}

AItem::AItem() : Super() {
	SetActorEnableCollision(false);
	SetGrade(1);
	
	SetMeshComponent(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent")));
	SetRootComponent(GetMeshComponent());
	GetMeshComponent()->SetStaticMesh(GetMesh());
}

EItemType AItem::GetType() {
	return type;
}

void AItem::SetType(EItemType newVal) {
	type = newVal;
}

FString AItem::GetName() {
	return name;
}

void AItem::SetName(FString newVal) {
	name = newVal;
}

void AItem::TakeFrom(AItem* otherItem) {
	// Get the amount of items needed to add
	int amountToAdd = otherItem->GetAmount();

	// Can we just add to this item
	if (GetRemainingSpace() >= amountToAdd) {
		SetAmount(GetAmount() + otherItem->GetAmount());
		otherItem->SetAmount(0);
	}
	else {
		// If we're greater than stack size just set the amount to max size
		otherItem->SetAmount(otherItem->GetAmount() - GetRemainingSpace());
		SetAmount(GetStackSize());
	}
}

int32 AItem::GetGrade() {
	return grade;
}

void AItem::SetGrade(int32 newVal) {
	grade = newVal;
}

ARPGCharacter* AItem::GetItemOwner() {
	return itemOwner;
}

int32 AItem::GetQuality()
{
	return quality;
}

void AItem::SetQuality(int32 newQuality)
{
	quality = newQuality;
}

void AItem::SetItemOwner(ARPGCharacter* newVal) {
	itemOwner = newVal;
}

bool AItem::HasSpace() {
	return GetAmount() < GetStackSize();
}

int32 AItem::GetRemainingSpace() {
	return GetStackSize() - GetAmount();
}

int32 AItem::GetAmount() {
	return amount;
}

void AItem::SetAmount(int32 newVal) {
	amount = newVal;
}

int32 AItem::GetStackSize() {
	return stackSize;
}

void AItem::SetStackSize(int32 newVal) {
	stackSize = newVal;
}

AItem* AItem::Copy() {
	return CreateItem(GetWorld(), GetItemOwner(), GetName(), GetAmount(), GetGrade(), GetQuality(), GetStackSize());
}

FString AItem::GetTooltipText()
{
	return "";
}

AItem * AItem::CreateItem(UWorld* world, ARPGCharacter* inOwner, FString inName, int32 inAmount, int32 inGrade, int32 inQuality, int32 inStackSize)
{
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AItem* newItem = world->SpawnActor<AItem>(AItem::StaticClass(), inOwner->GetTransform(), params);
	newItem->SetName(inName);
	newItem->SetAmount(inAmount);
	newItem->SetStackSize(inStackSize);
	//SetType(GetType());
	newItem->SetGrade(inGrade);
	newItem->SetItemOwner(inOwner);
	newItem->SetQuality(inQuality);
	return  newItem;
}
