// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FightCoreComponent.generated.h"

class UFightActionInputTrigger;

UENUM(BlueprintType)
enum class EInputConfig : uint8
{
	InputConfig_None = 0 UMETA(DisplayName = "None") ,
	InputConfig_Down = 1 UMETA(DisplayName = "Down"),
	InputConfig_Right = (1 << 1) UMETA(DisplayName = "Right") ,
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
		TArray<UFightActionInputTrigger *> FightActionInputTriggerArray;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	uint8 InputData;

	void MapInput();

private:

	void BindInput();

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
