#pragma once

#include "EHurdleType.generated.h"

UENUM(BlueprintType)
enum EHurdleType
{
	None  UMETA(DisplayName="Default"),
	Stone UMETA(DisplayName="Stone"),
	Branch UMETA(DisplayName="Branch"),
	Coin UMETA(DisplayName="Coin"),
	Rocket UMETA(DisplayName="Rocket"),
	SkateBoard UMETA(DisplayName="SkateBoard"),
};