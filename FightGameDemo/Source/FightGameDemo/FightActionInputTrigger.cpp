// Fill out your copyright notice in the Description page of Project Settings.


#include "FightActionInputTrigger.h"

UFightActionInputTrigger::UFightActionInputTrigger():
	CurrentCheckInputIndex(0)
{

}

EFightActionInputTriggerCheckResult UFightActionInputTrigger::ReciveInput(uint8 ActionInputData)
{
	check(CurrentCheckInputIndex != -1);


	if (CurrentCheckInputIndex == 0 &&
		ActionInputData == 0)
	{
		return EFightActionInputTriggerCheckResult::FightActionInputTriggerCheckResult_None;
	}


	bool UseSimplifyMatch = (CurrentCheckInputIndex != LastDirectionInputIndex);

	EInputCheckResult Resutlt = CurrentCheckInputConfig.CheckInput(ActionInputData);


	EFightActionInputTriggerCheckResult FightActionInputTriggerCheckResult = EFightActionInputTriggerCheckResult::FightActionInputTriggerCheckResult_None;
	switch (Resutlt)
	{
	case EInputCheckResult::InputCheckResult_Success:
	{
		if (CurrentCheckInputIndex == CurrentLastCheckInputIndex)
		{
			FightActionInputTriggerCheckResult = EFightActionInputTriggerCheckResult::FightActionInputTriggerCheckResult_Completed;
		}
		else
		{
			int NextInputCheckConfigIndex = CurrentCheckInputIndex + 1;
			const FInputCheckConfig& NextInputCheckConfig = CheckInputConfig[NextInputCheckConfigIndex];

			if (NextInputCheckConfig.InputConfig == CurrentCheckInputConfig.InputConfig)
			{
				CurrentLastCheckInputIndex++;
				CurrentLastDirectionInputIndex++;

				FInputCheckConfig NewCurrentCheckInputConfig = FInputCheckConfig(NextInputCheckConfig, CurrentCheckInputConfig);
				CurrentCheckInputConfig.SetUp(NewCurrentCheckInputConfig);
			}
			else
			{
				CurrentCheckInputIndex = NextInputCheckConfigIndex;

				FInputCheckConfig NewCurrentCheckInputConfig = FInputCheckConfig(NextInputCheckConfig,CurrentCheckInputConfig);

				CurrentCheckInputConfig.InputConfig = NewCurrentCheckInputConfig.InputConfig;
				CurrentCheckInputConfig.PreInputConfig = NewCurrentCheckInputConfig.PreInputConfig;
				CurrentCheckInputConfig.MaxCheckFrame = NewCurrentCheckInputConfig.MaxCheckFrame;
				CurrentCheckInputConfig.CurrentCheckFrame = 0;
			}

			FightActionInputTriggerCheckResult = EFightActionInputTriggerCheckResult::FightActionInputTriggerCheckResult_Success;
		}
	}
		break;
	case EInputCheckResult::InputCheckResult_Failed:
	{
		CurrentCheckInputIndex = 0;
		CurrentLastCheckInputIndex = LastCheckInputIndex;
		CurrentLastDirectionInputIndex = LastDirectionInputIndex;

		CurrentCheckInputConfig = CheckInputConfig[CurrentCheckInputIndex];

		FightActionInputTriggerCheckResult = EFightActionInputTriggerCheckResult::FightActionInputTriggerCheckResult_Failed;

		break;
	}
	case EInputCheckResult::InputCheckResult_TimeOut:
	{
		CurrentCheckInputIndex = 0;
		CurrentLastCheckInputIndex = LastCheckInputIndex;
		CurrentLastDirectionInputIndex = LastDirectionInputIndex;

		CurrentCheckInputConfig = CheckInputConfig[CurrentCheckInputIndex];

		FightActionInputTriggerCheckResult = EFightActionInputTriggerCheckResult::FightActionInputTriggerCheckResult_TimeOut;
	}
		break;
	case EInputCheckResult::InputCheckResult_None:
	default:
	{
		FightActionInputTriggerCheckResult = EFightActionInputTriggerCheckResult::FightActionInputTriggerCheckResult_None;
		CurrentCheckInputConfig.CheckFrameAdd();
	}
		break;
	}


	return FightActionInputTriggerCheckResult;
}

void UFightActionInputTrigger::PostLoad()
{
	Super::PostLoad();
}

bool UFightActionInputTrigger::SetUpData()
{
	if (CheckInputConfig.Num() == 0)
		return false;

	CurrentCheckInputConfig = CheckInputConfig[CurrentCheckInputIndex];

	LastCheckInputIndex = CheckInputConfig.Num() - 1;
	CurrentLastCheckInputIndex = LastCheckInputIndex;

	for (size_t i = LastCheckInputIndex; i != 0; i--)
	{
		const FInputCheckConfig& InputCheckConfig = CheckInputConfig[i];
		if ((uint8)InputCheckConfig.InputConfig & ((uint8)EActionInputConfig::ActionInputConfig_Back |
			(uint8)EActionInputConfig::ActionInputConfig_Forward |
			(uint8)EActionInputConfig::ActionInputConfig_Down |
			(uint8)EActionInputConfig::ActionInputConfig_Up))
		{
			LastDirectionInputIndex = i;
			CurrentLastDirectionInputIndex = LastDirectionInputIndex;
			break;
		}
	}

	return true;
}
