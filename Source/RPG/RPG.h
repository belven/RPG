// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/WidgetComponent.h"

#define mIsChildOf(inUObject, checkClass) inUObject != nullptr ? inUObject->GetClass()->IsChildOf(checkClass::StaticClass()) : false
#define lnBreak "\n"

#define GetRandomPercent rand() % 100
#define IsSuccess(chance) GetRandomPercent <= chance
#define IsCrit(critChance) IsSuccess(critChance)