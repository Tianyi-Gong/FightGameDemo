
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FightCoreHead.h"
#include "FightCoreComponent.generated.h"

class UFightActionInputTrigger;

UCLASS(Blueprintable , BlueprintType ,config = Game, meta = (BlueprintSpawnableComponent))
class UFightCoreComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFightCoreComponent();

	UPROPERTY()
		USkeletalMeshComponent*	MeshComponentRef;

	UPROPERTY()
		UInputComponent* InputComponentRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputConfig)
		TMap<EInputConfig, FKey> InputConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputConfig)
		TArray<TSubclassOf<UFightActionInputTrigger>> FightActionInputTriggerArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputConfig)
		TArray<UFightActionInputTrigger *> FightActionInputTriggerInstances;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputConfig)
		EPlayerPosition PlayerPosition = EPlayerPosition::PlayerPosition_Right;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	uint8 InputData;

	uint8 InputActionData;

	void MapInput();

	void MapActionInput();

private:

	void BindInput();

	void InitData();


	TArray<EInputConfig> InputCheck = {
		EInputConfig::InputConfig_Down,
		EInputConfig::InputConfig_Left,
		EInputConfig::InputConfig_Right,
		EInputConfig::InputConfig_Up,
		EInputConfig::InputConfig_LightPunche,
		EInputConfig::InputConfig_HeavyPunche,
		EInputConfig::InputConfig_LightKick,
		EInputConfig::InputConfig_HeavyKick
	};

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
