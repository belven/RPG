// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "Items/Equipable.h"
#include "Enums.h"
#include "Weapon.generated.h"

USTRUCT(BlueprintType)
struct FWeaponParams
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		float healthChange = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		float critChance = 15;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		float range = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		float attackSpeed = 0.5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		bool heals = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		EDamageType damageType = EDamageType::Physical;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		EQuality quality = EQuality::Base;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		int32 grade = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		bool twoHanded;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFired);

UCLASS(Blueprintable)
class AWeapon : public AEquipable
{
	GENERATED_BODY()
protected:
	FWeaponParams settings;
	bool canFire = true;
	float lastTime = 0;

public:
	AWeapon();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		float GetChangeAmount();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		float GetRange();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		float GetDPS();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		bool IsTwoHanded();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void SetIsTwoHanded(bool isTwoHanded);

	UFUNCTION(BlueprintCallable, Category = "Item")
		virtual AItem* Copy();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void SetChangeAmount(float newVal);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void SetRange(float newVal);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		virtual bool CanFire();

	virtual void Fire(class ARPGCharacter* targetr);

	virtual	void SetItemOwner(ARPGCharacter* inOwner) override;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		virtual void StopFire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		static AWeapon* CreateWeapon(UWorld* world, ARPGCharacter* inOwner, FWeaponParams inSettings);

	UPROPERTY(BlueprintAssignable, Category = "Events")
		FFired OnFire;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		float GetAttackSpeed();
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void SetAttackSpeed(float newVal);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		float GetCritChance();
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void SetCritChance(float newVal);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		bool Heals();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void SetHeals(bool newVal);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void SetSettings(FWeaponParams newSettings);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		EDamageType GetChangeAmountType();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		virtual float GetProgressBarPercent();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		virtual FString GetTooltipText() override;
};
