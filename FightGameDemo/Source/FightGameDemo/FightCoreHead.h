#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FightCoreHead.generated.h"

UENUM(BlueprintType) 
enum class EInputCheckResult : uint8
{
	InputCheckResult_None,
	InputCheckResult_Success,
	InputCheckResult_Failed,
	InputCheckResult_TimeOut
};

UENUM(BlueprintType)
enum class EPlayerPosition : uint8
{
	PlayerPosition_Left,
	PlayerPosition_Right
};

UENUM(BlueprintType)
enum class EInputConfig : uint8
{
	InputConfig_None = 0 UMETA(DisplayName = "None"),
	InputConfig_Down = 1 UMETA(DisplayName = "Down"),
	InputConfig_Right = (1 << 1) UMETA(DisplayName = "Right"),
	InputConfig_RightDown = ((1 << 1) + 1) UMETA(DisplayName = "RightDown"),
	InputConfig_Up = (1 << 2) UMETA(DisplayName = "Up"),
	InputConfig_RightUp = ((1 << 2) + (1 << 1)) UMETA(DisplayName = "RightUp"),
	InputConfig_Left = (1 << 3) UMETA(DisplayName = "Left"),
	InputConfig_LeftDown = ((1 << 3) + 1) UMETA(DisplayName = "LeftDown"),
	InputConfig_LeftUp = ((1 << 3) + (1 << 2)) UMETA(DisplayName = "LeftUp"),
	InputConfig_LightPunche = (1 << 4) UMETA(DisplayName = "LightPunche"),
	InputConfig_HeavyPunche = (1 << 5) UMETA(DisplayName = "HeavyPunche"),
	InputConfig_LightKick = (1 << 6) UMETA(DisplayName = "LightKick"),
	InputConfig_HeavyKick = (1 << 7) UMETA(DisplayName = "HeavyKick"),
};

UENUM(BlueprintType)
enum class EActionInputConfig : uint8
{
	ActionInputConfig_None = 0 UMETA(DisplayName = "None"),
	ActionInputConfig_Down = 1 UMETA(DisplayName = "Down"),
	ActionInputConfig_Forward = (1 << 1) UMETA(DisplayName = "Forward"),
	ActionInputConfig_ForwardDown = ((1 << 1) + 1) UMETA(DisplayName = "ForwardDown"),
	ActionInputConfig_Up = (1 << 2) UMETA(DisplayName = "Up"),
	ActionInputConfig_ForwardUp = ((1 << 2) + (1 << 1)) UMETA(DisplayName = "ForwardUp"),
	ActionInputConfig_Back = (1 << 3) UMETA(DisplayName = "Back"),
	ActionInputConfig_BackDown = ((1 << 3) + 1) UMETA(DisplayName = "BackDown"),
	ActionInputConfig_BackUp = ((1 << 3) + (1 << 2)) UMETA(DisplayName = "BackUp"),
	ActionInputConfig_LightPunche = (1 << 4) UMETA(DisplayName = "LightPunche"),
	ActionInputConfig_HeavyPunche = (1 << 5) UMETA(DisplayName = "HeavyPunche"),
	ActionInputConfig_LightKick = (1 << 6) UMETA(DisplayName = "LightKick"),
	ActionInputConfig_HeavyKick = (1 << 7) UMETA(DisplayName = "HeavyKick"),
};