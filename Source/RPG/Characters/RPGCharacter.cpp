// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "RPGCharacter.h"
#include "Projectiles/RPGProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "UI/HealthBarCPP.h"
#include "ConstructorHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Actions/Actions.h"
#include "Weapons/Sword.h"
#include "Items/Inventory.h"
#include "Array.h"
#include "Items/Item.h"
#include "RPG.h"
#include "Actions/StaggerAction.h"
#include "LogMacros.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

ARPGCharacter::ARPGCharacter()
{
	SetMaxHealth(100);
	SetCurrentHealth(GetMaxHealth());

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	SetRootComponent(GetCapsuleComponent());

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	rollDistance = 400;
	rollVelocity = 300;

	SetCharacterMesh(CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P")));
	GetCharacterMesh()->bCastDynamicShadow = false;
	GetCharacterMesh()->CastShadow = true;
	GetCharacterMesh()->SetupAttachment(GetCapsuleComponent());
	GetCharacterMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetCharacterMesh()->SetRelativeRotation(FRotator(0, -90, 0));


	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCharacterMesh());
	FirstPersonCameraComponent->RelativeLocation = FVector(0.0F, -150.0F, 200.0F);
	FirstPersonCameraComponent->RelativeRotation = FRotator(-90, 0, 0);
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	static ConstructorHelpers::FClassFinder<UHealthBarCPP> healthBarWidget(TEXT("/Game/FirstPersonCPP/Blueprints/UI/CharacterUI/HealthBarBP.HealthBarBP_C"));

	if (healthBarWidget.Succeeded())
	{
		healthBarWidgetClass = healthBarWidget.Class;
		SetHealthBarComponent(CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Bar Component")));
		GetHealthBarComponent()->SetupAttachment(RootComponent);
		GetHealthBarComponent()->SetOwnerNoSee(true);
	}
}

float ARPGCharacter::GetShortestWeaponRange()
{
	float range = -1;
	TArray<AWeapon*> weaponsEquiped;
	equipedWeapons.GenerateValueArray(weaponsEquiped);

	for (AWeapon* weapon : weaponsEquiped)
	{
		if (range == -1)
		{
			range = weapon->GetRange();
		}
		else
		{
			range = weapon->GetRange() < range ? weapon->GetRange() : range;
		}
	}

	return range == -1 ? 130 : range;
}

void ARPGCharacter::AttackStart(ARPGCharacter* target)
{
	if (CanPerformAction(EActionType::Attack) && GetEquipedWeapons().Num() > 0)
	{
		GetCharacterMovement()->StopMovementImmediately();
		PerformAction(EActionType::Attack, 1.0);
	}
}

void ARPGCharacter::AttackEnd()
{
	UAttackAction* attackAction = Cast<UAttackAction>(GetActionByType(EActionType::Attack));

	if (attackAction != nullptr)
	{
		if (attackAction->GetTarget() != nullptr
			&& attackAction->GetTarget()->GetCurrentHealth() > 0)
		{
			float dist = FVector::Distance(GetActorLocation(), attackAction->GetTarget()->GetActorLocation());

			if (dist <= 130)
			{
				FDamageEvent damageEvent;
				attackAction->GetTarget()->TakeDamage(10, damageEvent, GetController(), this);
			}
		}
	}
	ClearActions();
}

void ARPGCharacter::Landed(const FHitResult& Hit)
{
	ACharacter::Landed(Hit);
	//ClearActions();
}

void ARPGCharacter::Jump()
{
	if (IsPerformingAction(EActionType::None))
	{
		Super::Jump();
	}
}

bool ARPGCharacter::CanSee(AActor * other)
{
	FHitResult hit;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(hit, GetActorLocation(), other->GetActorLocation(), ECollisionChannel::ECC_Camera, params);

	if (hit.bBlockingHit && hit.GetActor() == other)
	{
		return true;
	}

	return false;
}

void ARPGCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	CreateWidgets();

	ASword* sword = ASword::CreateSword(this, 10, 150, 1);
	inventory = NewObject<UInventory>(UInventory::StaticClass());
	inventory->SetMaxItemCount(10);

	inventory->AddItem(sword);
	equipedWeapons.Add(EWeaponPosition::RightHand, sword);
	sword->Equip();

	const FName TraceTag("MyTraceTag");

	GetWorld()->DebugDrawTraceTag = TraceTag;
}

void ARPGCharacter::Attack()
{
	FHitResult hit = FHitResult();
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	//params.TraceTag = TraceTag;

	FVector distance = GetActorForwardVector() * GetShortestWeaponRange();

	GetWorld()->LineTraceSingleByChannel(hit, GetActorLocation(), GetActorLocation() + distance, ECollisionChannel::ECC_Pawn, params);

	if (hit.bBlockingHit && mIsChildOf(hit.GetActor(), ARPGCharacter))
	{
		ARPGCharacter* character = Cast<ARPGCharacter>(hit.GetActor());
		AttackStart(character);
	}
}

bool ARPGCharacter::CanBlock()
{
	// TODO
	return false;
}

void ARPGCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up game play key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ARPGCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Parry", IE_Released, this, &ARPGCharacter::Parry);

	PlayerInputComponent->BindAction("Dodge", IE_Pressed, this, &ARPGCharacter::Dodge);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ARPGCharacter::Attack);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARPGCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARPGCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turn rate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ARPGCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ARPGCharacter::LookUpAtRate);
}

void ARPGCharacter::Parry()
{
	if (CanPerformAction(EActionType::Parry))
	{
		PerformAction(EActionType::Parry, 1.0);
		UE_LOG(CombatLog, Log, TEXT("%s used parry"), *this->GetName());
	}
}

void ARPGCharacter::OnFire()
{
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			const FRotator SpawnRotation = GetControlRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			// spawn the projectile at the muzzle
			ARPGProjectile* projectile = World->SpawnActor<ARPGProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

			if (projectile != nullptr) projectile->SetProjectileOwner(this);
		}
	}

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation != NULL)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = GetCharacterMesh()->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

float ARPGCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (IsPerformingAction(EActionType::Parry))
	{
		ARPGCharacter* character = Cast<ARPGCharacter>(DamageCauser);

		if (character)
		{
			ClearActions();
			character->InterruptAction(EActionType::Parry, this);
			FDamageEvent damageEvent;
			UE_LOG(CombatLog, Log, TEXT("%s parried %s"), *this->GetName(), *character->GetName());
		}
	}
	else if (!IsDodging())
	{
		if (IsPerformingAction(EActionType::Block))
		{
			Damage *= 0.5;
		}
		else if (IsPerformingAction(EActionType::Stagger))
		{
			Damage *= 2;
		}

		currentHealth -= Damage;

		UE_LOG(CombatLog, Log, TEXT("%s dealt %d damage to %s"), *DamageCauser->GetName(), Damage, *this->GetName());

		if (currentHealth <= 0)
		{
			Destroy();
		}
	}

	return Damage;
}

void ARPGCharacter::MoveForward(float Value)
{
	if (Value != 0.0f && IsPerformingAction(EActionType::None))
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ARPGCharacter::MoveRight(float Value)
{
	if (Value != 0.0f && IsPerformingAction(EActionType::None))
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ARPGCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ARPGCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ARPGCharacter::Dodge()
{
	if (!IsDodging() && !GetMovementComponent()->IsFalling())
	{
		if (CanPerformAction(EActionType::Dodge))
		{
			PerformAction(EActionType::Dodge, 1.0);

			FVector direction;

			GetMovementComponent()->StopMovementImmediately();

			if (GetVelocity().Size() < 10)
			{
				direction = (GetActorForwardVector() * (0 - rollDistance)) + FVector(0, 0, 1) * rollVelocity;
			}
			else
			{
				direction = GetVelocity() * 2;
			}

			LaunchCharacter(direction, false, false);


		}
	}
}

void ARPGCharacter::PerformAction(EActionType type, float duration)
{
	ClearActions();

	switch (type)
	{
	case EActionType::Attack:
		UAttackAction* attackAction = UAttackAction::CreateAttackAction();
		//attackAction->SetTarget(target);
		attackAction->SetWeaponsUsed(equipedWeapons);
		AddAction(attackAction);
		GetWorld()->GetTimerManager().SetTimer(ActionTimer, this, &ARPGCharacter::AttackEnd, attackAction->GetDuration(), true);
		GetWorld()->GetTimerManager().SetTimer(ActionTimer, this, &ARPGCharacter::ClearActions, attackAction->GetDuration(), true);
		break;
	case EActionType::Dodge:
		UDodgeAction* dodgeAction = UDodgeAction::CreateDodgeAction();
		AddAction(dodgeAction);
		GetWorld()->GetTimerManager().SetTimer(ActionTimer, this, &ARPGCharacter::ClearActions, dodgeAction->GetDuration(), true);
		break;
	case EActionType::Block:
		UBlockAction* blockAction = UBlockAction::CreateBlockAction();
		AddAction(blockAction);
		GetWorld()->GetTimerManager().SetTimer(ActionTimer, this, &ARPGCharacter::ClearActions, blockAction->GetDuration(), true);
		break;
	case EActionType::Parry:
		UParryAction* parryAction = UParryAction::CreateParryAction();
		parryAction->SetDuration(duration);
		AddAction(parryAction);
		GetWorld()->GetTimerManager().SetTimer(ActionTimer, this, &ARPGCharacter::ClearActions, parryAction->GetDuration(), true);
		break;
	case EActionType::Stagger:
		UStaggerAction* stagger = UStaggerAction::CreateStaggerAction();
		AddAction(stagger);
		GetWorld()->GetTimerManager().ClearTimer(ActionTimer);
		break;
	default:
		break;
	}
}

void ARPGCharacter::CreateWidgets()
{
	healthBar = CreateWidget<UHealthBarCPP>(GetWorld(), healthBarWidgetClass);
	healthBar->SetOwner(this);
	GetHealthBarComponent()->SetWidget(healthBar);
	GetHealthBarComponent()->SetDrawSize(FVector2D(100, 20));

	FTransform trans;
	trans.SetLocation(FVector(0.0, 8.0, 100.0));

	GetHealthBarComponent()->SetRelativeTransform(trans);

	GetHealthBarComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

bool ARPGCharacter::IsDodging()
{
	return IsPerformingAction(EActionType::Dodge);
}

void ARPGCharacter::InterruptAction(EActionType interruptCause, ARPGCharacter* interrupter)
{
	if (IsPerformingAction(EActionType::Attack))
	{
		GetMovementComponent()->StopMovementImmediately();

		float duration = 1.0F;

		if (interruptCause == EActionType::Parry)
		{
			duration = 2.0F;
		}

		PerformAction(EActionType::Stagger, duration);
		OnInterrupt.Broadcast(interruptCause, interrupter);
	}
}

bool ARPGCharacter::CanParry()
{
	// TODO
	return false;
}

const bool ARPGCharacter::CanPerformAction(EActionType type)
{
	for (UCharacterAction* action : GetCurrentActions())
	{
		if (!action->CanBeCancelled())
		{
			return false;
		}
	}
	return true;
}

bool ARPGCharacter::IsPerformingAction(EActionType type)
{
	if (GetCurrentActions().Num() == 0)
	{
		return type == EActionType::None;
	}
	else
	{
		for (UCharacterAction* action : GetCurrentActions())
		{
			if (action->GetActionType() == type)
				return true;
		}
	}
	return false;
}

void ARPGCharacter::ClearActions()
{
	GetPrieviousActions().Empty();
	for (UCharacterAction* action : GetCurrentActions())
	{
		prieviousActions.Add(action);
	}
	GetCurrentActions().Empty();
	UE_LOG(CombatLog, Log, TEXT("%s actions ready"), *this->GetName());
}

void ARPGCharacter::AddAction(UCharacterAction* newAction)
{
	currentActions.Add(newAction);
}

UCharacterAction* ARPGCharacter::GetActionByType(EActionType type)
{
	if (GetCurrentActions().Num() > 0)
	{
		for (UCharacterAction* action : GetCurrentActions())
		{
			if (action->GetActionType() == type)
				return action;
		}
	}
	return nullptr;
}

FHitResult ARPGCharacter::GetTraceToTarget(ARPGCharacter* character)
{
	FHitResult hit = FHitResult();
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(hit, GetActorLocation(), character->GetActorLocation(), ECollisionChannel::ECC_Camera, params);
	return hit;
}
