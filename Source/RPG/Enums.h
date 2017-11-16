#pragma once
UENUM(BlueprintType)
enum class EActionType : uint8
{
	None,
	Parry,
	Attack,
	Block,
	Dodge,
	Stagger
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Armour,
	Weapon,
	Resource,
	End
}; 

UENUM(BlueprintType)
enum class EWeaponPosition : uint8
{
	LeftHand,
	RightHand
};

UENUM(BlueprintType)
enum class EQuality : uint8
{
	Base,
	Iron,
	Steel,
	Titianium,
	Unobtainium,
	End
};

UENUM(BlueprintType)
enum class EDamageType : uint8
{
	Physical,
	Blast,
	Energy
};