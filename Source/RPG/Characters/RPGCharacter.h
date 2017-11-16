// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WidgetComponent.h"
#include "Enums.h"
#include "RPGCharacter.generated.h"

class UInputComponent;
class UHealthBarCPP;
class UCharacterAction;
class UInventory;
class AItem;
class AWeapon;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActionInterrupted, EActionType, interruptCasue, ARPGCharacter*, interrupter);

UCLASS(config = Game)
class ARPGCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* characterMesh;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USceneComponent* FP_MuzzleLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, Category = "Health")
		float currentHealth;

	UPROPERTY(EditAnywhere, Category = "Health")
		float maxHealth;

	UPROPERTY()
		class UHealthBarCPP* healthBar;

	UPROPERTY()
		class UWidgetComponent* healthBarComponent = nullptr;

	TSubclassOf<UHealthBarCPP> healthBarWidgetClass;

	UFUNCTION(BlueprintCallable, Category = "Widgets")
		void CreateWidgets();

	UPROPERTY()
		TArray<UCharacterAction*> currentActions;

	UPROPERTY()
		TArray<UCharacterAction*> prieviousActions;

	UPROPERTY()
		TMap<EWeaponPosition, AWeapon*> equipedWeapons;

	UPROPERTY()
		float rollDistance;

	UPROPERTY()
		float rollVelocity;

	UPROPERTY()
		UInventory* inventory;

	FTimerHandle ActionTimer;

public:
	ARPGCharacter();
	UFUNCTION(BlueprintCallable, Category = "Action")
		UCharacterAction* GetActionByType(EActionType type);

	FActionInterrupted OnInterrupt;

	UFUNCTION(BlueprintCallable, Category = "Action")
		float GetShortestWeaponRange();

	UFUNCTION(BlueprintCallable, Category = "Action")
		const bool CanPerformAction(EActionType type);

	UFUNCTION(BlueprintCallable, Category = "Action")
		void ClearActions();

	UFUNCTION(BlueprintCallable, Category = "Action")
		void AddAction(UCharacterAction* newAction);

	UFUNCTION(BlueprintCallable, Category = "Action")
		virtual void AttackStart(ARPGCharacter* target);

	UFUNCTION(BlueprintCallable, Category = "Action")
		virtual void AttackEnd();

	UFUNCTION(BlueprintCallable, Category = "Actions")
		virtual bool IsPerformingAction(EActionType type);

	UFUNCTION(BlueprintCallable, Category = "Health")
		class UHealthBarCPP* GetHealthBar() { return healthBar; }

	UFUNCTION(BlueprintCallable, Category = "Health")
		void SetHealthBar(class UHealthBarCPP* val) { healthBar = val; }

	UFUNCTION(BlueprintCallable, Category = "Health")
		class UWidgetComponent* GetHealthBarComponent() { return healthBarComponent; }

	UFUNCTION(BlueprintCallable, Category = "Health")
		void SetHealthBarComponent(class UWidgetComponent* val) { healthBarComponent = val; }

	virtual void Landed(const FHitResult& Hit) override;
	virtual void Jump() override;

	UFUNCTION(BlueprintCallable, Category = "Health")
		float GetCurrentHealth() { return currentHealth; }

	UFUNCTION(BlueprintCallable, Category = "Health")
		void SetCurrentHealth(float val) { currentHealth = val; }

	UFUNCTION(BlueprintCallable, Category = "Health")
		float GetMaxHealth() { return maxHealth; }

	UFUNCTION(BlueprintCallable, Category = "Health")
		void SetMaxHealth(float val) { maxHealth = val; }

	UFUNCTION(BlueprintCallable, Category = "Vision")
		virtual bool CanSee(AActor* other);

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ARPGProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* FireAnimation;
	
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UFUNCTION(BlueprintCallable, Category = "Dodge")
		virtual void Dodge();

	void PerformAction(EActionType type, float duration);
	FHitResult GetTraceToTarget(ARPGCharacter* character);

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable, Category = "Actions")
		bool IsDodging();

	UFUNCTION(BlueprintCallable, Category = "Actions")
		TArray<UCharacterAction *>& GetCurrentActions() { return currentActions; }

	UFUNCTION(BlueprintCallable, Category = "Actions")
		TArray<UCharacterAction *>& GetPrieviousActions() { return prieviousActions; }

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		UInventory* GetInventory() { return inventory; }

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		void SetInventory(UInventory* val) { inventory = val; }

	UFUNCTION(BlueprintCallable, Category = "Weapons")
		TMap<EWeaponPosition, AWeapon *>& GetEquipedWeapons() { return equipedWeapons; }


	UFUNCTION(BlueprintCallable, Category = "EDITME")
		class USkeletalMeshComponent* GetCharacterMesh() { return characterMesh; }

	UFUNCTION(BlueprintCallable, Category = "EDITME")
		void SetCharacterMesh(class USkeletalMeshComponent* val) { characterMesh = val; }

	UFUNCTION(BlueprintCallable, Category = "Attack")
		void Attack();
	bool CanBlock();
protected:
	virtual void BeginPlay();

	/** Fires a projectile. */
	void OnFire();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles strafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	void Parry();
	// End of APawn interface
public:
	virtual void InterruptAction(EActionType interruptCause, ARPGCharacter* interrupter);
	bool CanParry();
};