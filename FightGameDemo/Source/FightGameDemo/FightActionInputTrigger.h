// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FightCoreComponent.h"
#include "FightActionInputTrigger.generated.h"

USTRUCT(BlueprintType)
struct FIGHTGAMEDEMO_API FInputCheckConfig
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputConfig)
		EInputConfig InputConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputConfig)
		int MaxCheckFrame;

	FInputCheckConfig() :
		InputConfig(EInputConfig::InputConfig_None),
		MaxCheckFrame(5)
	{

	}
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, config = Game, meta = (BlueprintSpawnableComponent))
class FIGHTGAMEDEMO_API UFightActionInputTrigger : public UObject
{
	GENERATED_BODY()

public:
	UFightActionInputTrigger();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputConfig)
		TArray<FInputCheckConfig> CheckInputConfig;

	void ReciveInput(EInputConfig InputConfig, bool& bMapResult);

	void PostLoad() override;

protected:

	int CurrentCheckInputIndex;

	FInputCheckConfig CurrentCheckInputConfig;
};
