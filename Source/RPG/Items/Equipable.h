// Copyright of Explosive Industries

#pragma once

#include "Item.h"
#include "Equipable.generated.h"

/**
 * 
 */
UCLASS()
class  AEquipable : public AItem
{
	GENERATED_BODY()
private:
	bool equipped = false;

public:
	virtual void Equip();
	virtual void Unequip();		
	bool IsEquipped() const { return equipped; }
	void SetEquipped(bool val) { equipped = val; }
};
