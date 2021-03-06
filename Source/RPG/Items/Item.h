///////////////////////////////////////////////////////////
//  AItem.h
//  Implementation of the Class AItem
//  Created on:      04-May-2015 11:16:11
//  Original author: sam
///////////////////////////////////////////////////////////


#pragma once
#include "UnrealString.h"
#include "Enums.h"
#include "Item.generated.h"

class ARPGCharacter;

UCLASS(Blueprintable)
class AItem : public AActor
{
	GENERATED_BODY()
public:
	AItem();

	UFUNCTION(BlueprintCallable, Category = "Item")
		EItemType GetType();

	UFUNCTION(BlueprintCallable, Category = "Item")
		void SetQuality(int32 newQuality);

	UFUNCTION(BlueprintCallable, Category = "Item")
		int32 GetQuality();

	UFUNCTION(BlueprintCallable, Category = "Item")
		void SetType(EItemType newVal);

	UFUNCTION(BlueprintCallable, Category = "Item")
		FString GetName();

	UFUNCTION(BlueprintCallable, Category = "Item")
		void SetName(FString newVal);

	UFUNCTION(BlueprintCallable, Category = "Item")
		void TakeFrom(AItem* otherItem);

	UFUNCTION(BlueprintCallable, Category = "Item")
		int32 GetGrade();

	UFUNCTION(BlueprintCallable, Category = "Item")
		void SetGrade(int32 newVal);

	UFUNCTION(BlueprintCallable, Category = "Item")
		ARPGCharacter* GetItemOwner();

	UFUNCTION(BlueprintCallable, Category = "Item")
		virtual void SetItemOwner(ARPGCharacter* newVal);

	UFUNCTION(BlueprintCallable, Category = "Item")
		bool HasSpace();

	UFUNCTION(BlueprintCallable, Category = "Item")
		int32 GetRemainingSpace();

	UFUNCTION(BlueprintCallable, Category = "Item")
		int32 GetAmount();

	UFUNCTION(BlueprintCallable, Category = "Item")
		void SetAmount(int32 newVal);

	UFUNCTION(BlueprintCallable, Category = "Item")
		int32 GetStackSize();

	UFUNCTION(BlueprintCallable, Category = "Item")
		void SetStackSize(int32 newVal);

	UFUNCTION(BlueprintCallable, Category = "Item")
		virtual AItem* Copy();

	UFUNCTION(BlueprintCallable, Category = "Item")
		virtual FString GetTooltipText();

	UFUNCTION(BlueprintCallable, Category = "Item")
		static AItem* CreateItem(UWorld* world, ARPGCharacter* inOwner, FString inName = "Test", int32 inAmount = 1, int32 inGrade = 0, int32 inQuality = 0, int32 inStackSize = 3);

	FORCEINLINE AItem& operator+(AItem &aitem)
	{
		AItem* nitem = aitem.Copy();
		nitem->amount = aitem.amount + amount;
		return *nitem;
	}

	FORCEINLINE AItem& operator+=(AItem &aitem)
	{
		amount += aitem.amount;
		return *this;
	}

	FORCEINLINE AItem& operator-(AItem &aitem)
	{
		AItem* nitem = aitem.Copy();
		nitem->amount = aitem.amount - amount;
		return *nitem;
	}

	FORCEINLINE AItem& operator-=(AItem &aitem)
	{
		amount -= aitem.amount;
		return *this;
	}

	static int32 HighestItemLevel;

	void CloneItemSettings(AItem* cloneFromItem);

	UFUNCTION(BlueprintCallable, Category = "EDITME")
		class UStaticMesh* GetMesh() { return mesh; }

	UFUNCTION(BlueprintCallable, Category = "EDITME")
		void SetMesh(class UStaticMesh* val) { mesh = val; }

	UFUNCTION(BlueprintCallable, Category = "EDITME")
		UStaticMeshComponent* GetMeshComponent() { return meshComponent; }

	UFUNCTION(BlueprintCallable, Category = "EDITME")
		void SetMeshComponent(UStaticMeshComponent* val) { meshComponent = val; }
protected:
	UPROPERTY()
		EItemType type;

	UPROPERTY()
		FString name;
	
	UPROPERTY()
		class UStaticMesh* mesh;

	UPROPERTY()
		int32 grade = 1;

	UPROPERTY()
		ARPGCharacter* itemOwner;

	UPROPERTY()
		int32 amount = 1;

	UPROPERTY()
		int32 stackSize = 1;

	UPROPERTY()
		int32 quality = 0;
private:
	UStaticMeshComponent* meshComponent;
};