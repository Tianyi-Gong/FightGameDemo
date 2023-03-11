// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FightCoreComponent.h"
#include "FightCoreHead.h"
#include "FightActionInputTrigger.generated.h"

UENUM(BlueprintType)
enum class EFightActionInputTriggerCheckResult : uint8
{
	FightActionInputTriggerCheckResult_None,
	FightActionInputTriggerCheckResult_Completed,
	FightActionInputTriggerCheckResult_Failed,
	FightActionInputTriggerCheckResult_Success,
};


USTRUCT(BlueprintType)
struct FIGHTGAMEDEMO_API FInputCheckConfig
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputConfig)
		EActionInputConfig InputConfig;

	EActionInputConfig PreInputConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputConfig)
		int MaxCheckFrame;

	int CurrentCheckFrame;

	FInputCheckConfig() :
		InputConfig(EActionInputConfig::ActionInputConfig_None),
		PreInputConfig(EActionInputConfig::ActionInputConfig_None),
		MaxCheckFrame(5),
		CurrentCheckFrame(0)
	{

	}

	FInputCheckConfig(const FInputCheckConfig& CurrentInputCheckConfig, const FInputCheckConfig& PreInputCheckConfig)
	{
		InputConfig = CurrentInputCheckConfig.InputConfig;
		PreInputConfig = PreInputCheckConfig.InputConfig;
		MaxCheckFrame = CurrentInputCheckConfig.MaxCheckFrame;
		CurrentCheckFrame = 0;
	}

	FInputCheckConfig(const FInputCheckConfig& InputCheckConfig)
	{
		InputConfig = InputCheckConfig.InputConfig;
		PreInputConfig = InputCheckConfig.InputConfig;
		MaxCheckFrame = InputCheckConfig.MaxCheckFrame;
		CurrentCheckFrame = 0;
	}

	void SetUp(const FInputCheckConfig& InputCheckConfig)
	{
		InputConfig = InputCheckConfig.InputConfig;
		PreInputConfig = InputCheckConfig.InputConfig;
		MaxCheckFrame = InputCheckConfig.MaxCheckFrame;
		CurrentCheckFrame = 0;
	}

	EInputCheckResult CheckInput(uint8 InputData, bool bUseSimplifyMatch = true)
	{
		if (CurrentCheckFrame >= MaxCheckFrame)
		{
			return EInputCheckResult::InputCheckResult_TimeOut;
		}

		EInputCheckResult checkResult;
		if (InputData == (uint8)EActionInputConfig::ActionInputConfig_None &&
			InputConfig != EActionInputConfig::ActionInputConfig_None)
		{
			checkResult = EInputCheckResult::InputCheckResult_None;
		}
		else if(InputData & (uint8)PreInputConfig)
		{
			checkResult = EInputCheckResult::InputCheckResult_None;
		}
		else
		{
			if (bUseSimplifyMatch)
			{
				checkResult = (InputData & (uint8)InputConfig) ? EInputCheckResult::InputCheckResult_Success : EInputCheckResult::InputCheckResult_Failed;
			}
			else
			{
				checkResult = (InputData == (uint8)InputConfig) ? EInputCheckResult::InputCheckResult_Success : EInputCheckResult::InputCheckResult_Failed;
			}
		}
		return checkResult;
	}

	void CheckFrameAdd()
	{
		CurrentCheckFrame++;
	}
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, config = Game, meta = (BlueprintSpawnableComponent))
class UFightActionInputTrigger : public UObject
{
	GENERATED_BODY()

public:
	UFightActionInputTrigger();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputConfig)
		TArray<FInputCheckConfig> CheckInputConfig;

	UFUNCTION()
	EFightActionInputTriggerCheckResult ReciveInput(uint8 ActionInputData);

	void PostLoad() override;

protected:
	int CurrentCheckInputIndex = -1;

	int LastCheckInputIndex = -1;
	int CurrentLastCheckInputIndex = -1;

	int LastDirectionInputIndex = -1;
	int CurrentLastDirectionInputIndex = -1;

	FInputCheckConfig CurrentCheckInputConfig;
};
