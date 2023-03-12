// Fill out your copyright notice in the Description page of Project Settings.


#include "FightActionInputTrigger.h"

UFightActionInputTrigger::UFightActionInputTrigger():
	CurrentCheckInputIndex(0)
{

}

EFightActionInputTriggerCheckResult UFightActionInputTrigger::ReciveInput(uint8 ActionInputData)
{
	check(CurrentCheckInputIndex != -1);
	if (ActionInputData == PreCheckInputData &&
		FightActionInputTriggerState == EFightActionInputTriggerState::FightActionInputTriggerState_InProgress)
	{
		bool isTimeOut = CurrentCheckInputConfig.CheckFrameAdd();

		if (!isTimeOut)
		{
			return EFightActionInputTriggerCheckResult::FightActionInputTriggerCheckResult_None;
		}
		else
		{
			PreCheckInputData = 0;
			CurrentCheckInputIndex = 0;
			CurrentLastCheckInputIndex = LastCheckInputIndex;
			CurrentLastDirectionInputIndex = LastDirectionInputIndex;

			CurrentCheckInputConfig = CheckInputConfig[CurrentCheckInputIndex];

			FightActionInputTriggerState = EFightActionInputTriggerState::FightActionInputTriggerState_Idle;

			return EFightActionInputTriggerCheckResult::FightActionInputTriggerCheckResult_TimeOut;
		}
	}

	PreCheckInputData = ActionInputData;

	if (FightActionInputTriggerState == EFightActionInputTriggerState::FightActionInputTriggerState_Idle &&
		ActionInputData == 0)
	{
		return EFightActionInputTriggerCheckResult::FightActionInputTriggerCheckResult_None;
	}
	else if(FightActionInputTriggerState == EFightActionInputTriggerState::FightActionInputTriggerState_Complete)
	{
		if (ActionInputData != 0)
		{
			FInputCheckConfig& LastDirectionInputCheckConfig = CheckInputConfig[LastDirectionInputIndex];
				
			EInputCheckResult Resutlt = LastDirectionInputCheckConfig.CheckInput(ActionInputData);

			if (Resutlt == EInputCheckResult::InputCheckResult_Success)
			{
				return EFightActionInputTriggerCheckResult::FightActionInputTriggerCheckResult_None;
			}

			FInputCheckConfig& LastCheckInputCheckConfig = CheckInputConfig[LastCheckInputIndex];

			Resutlt = LastCheckInputCheckConfig.CheckInput(ActionInputData);

			if (Resutlt != EInputCheckResult::InputCheckResult_Success)
			{
				FightActionInputTriggerState = EFightActionInputTriggerState::FightActionInputTriggerState_Idle;
				return EFightActionInputTriggerCheckResult::FightActionInputTriggerCheckResult_Failed;
			}
			else
			{
				return EFightActionInputTriggerCheckResult::FightActionInputTriggerCheckResult_None;
			}
		}
		else
		{
			return EFightActionInputTriggerCheckResult::FightActionInputTriggerCheckResult_None;
		}

	}

	bool UseSimplifyMatch = (CurrentCheckInputIndex != LastDirectionInputIndex);

	EInputCheckResult Resutlt = CurrentCheckInputConfig.CheckInput(ActionInputData, UseSimplifyMatch);


	EFightActionInputTriggerCheckResult FightActionInputTriggerCheckResult = EFightActionInputTriggerCheckResult::FightActionInputTriggerCheckResult_None;
	switch (Resutlt)
	{
	case EInputCheckResult::InputCheckResult_Success:
	{
		if (CurrentCheckInputIndex == CurrentLastCheckInputIndex)
		{
			FightActionInputTriggerState = EFightActionInputTriggerState::FightActionInputTriggerState_Complete;
			FightActionInputTriggerCheckResult = EFightActionInputTriggerCheckResult::FightActionInputTriggerCheckResult_Completed;
		}
		else
		{
			int NextInputCheckConfigIndex = CurrentCheckInputIndex + 1;
			const FInputCheckConfig& NextInputCheckConfig = CheckInputConfig[NextInputCheckConfigIndex];

			if (NextInputCheckConfig.InputConfig == CurrentCheckInputConfig.InputConfig)
			{
				//CurrentLastCheckInputIndex++;
				//CurrentLastDirectionInputIndex++;

				//FInputCheckConfig NewCurrentCheckInputConfig = FInputCheckConfig(FInputCheckConfig(), CurrentCheckInputConfig);
				//CurrentCheckInputConfig.SetUp(NewCurrentCheckInputConfig);
				CurrentCheckInputConfig = FInputCheckConfig(FInputCheckConfig(CurrentCheckInputConfig.MaxCheckFrame), CurrentCheckInputConfig);
			}
			else
			{
				CurrentCheckInputIndex = NextInputCheckConfigIndex;

				CurrentCheckInputConfig = FInputCheckConfig(NextInputCheckConfig, CurrentCheckInputConfig);
				//FInputCheckConfig NewCurrentCheckInputConfig = FInputCheckConfig(NextInputCheckConfig,CurrentCheckInputConfig);
				//CurrentCheckInputConfig.SetUp(NewCurrentCheckInputConfig);
			}

			FightActionInputTriggerState = EFightActionInputTriggerState::FightActionInputTriggerState_InProgress;
			FightActionInputTriggerCheckResult = EFightActionInputTriggerCheckResult::FightActionInputTriggerCheckResult_Success;
		}
	}
		break;
	case EInputCheckResult::InputCheckResult_Failed:
	{
		PreCheckInputData = 0;
		CurrentCheckInputIndex = 0;
		CurrentLastCheckInputIndex = LastCheckInputIndex;
		CurrentLastDirectionInputIndex = LastDirectionInputIndex;

		CurrentCheckInputConfig = CheckInputConfig[CurrentCheckInputIndex];

		FightActionInputTriggerState = EFightActionInputTriggerState::FightActionInputTriggerState_Idle;
		FightActionInputTriggerCheckResult = EFightActionInputTriggerCheckResult::FightActionInputTriggerCheckResult_Failed;

		break;
	}
	case EInputCheckResult::InputCheckResult_TimeOut:
	{
		PreCheckInputData = 0;
		CurrentCheckInputIndex = 0;
		CurrentLastCheckInputIndex = LastCheckInputIndex;
		CurrentLastDirectionInputIndex = LastDirectionInputIndex;

		CurrentCheckInputConfig = CheckInputConfig[CurrentCheckInputIndex];

		FightActionInputTriggerState = EFightActionInputTriggerState::FightActionInputTriggerState_Idle;
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
