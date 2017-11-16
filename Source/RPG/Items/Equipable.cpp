// Copyright of Explosive Industries

#include "Equipable.h"
#include "RPG.h"
#include "Characters/RPGCharacter.h"
#include "GameFramework/Actor.h"

void AEquipable::Equip()
{
	if (GetItemOwner() != nullptr && GetItemOwner()->GetCharacterMesh() != nullptr)
	{
		AttachToComponent(GetItemOwner()->GetCharacterMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false), "RightHand");
		SetActorHiddenInGame(false);
		SetEquipped(true);
	}
}

void AEquipable::Unequip()
{
	GetItemOwner()->GetCharacterMesh()->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepRelative, true));
	SetActorHiddenInGame(true);
	SetEquipped(false);
}
