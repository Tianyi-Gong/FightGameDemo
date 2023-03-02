// Fill out your copyright notice in the Description page of Project Settings.


#include "FightCoreComponent.h"
#include "FightActionInputTrigger.h"

// Sets default values for this component's properties
UFightCoreComponent::UFightCoreComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	InputConfig.Add(EInputConfig::InputConfig_Down, EKeys::S);
	InputConfig.Add(EInputConfig::InputConfig_Left, EKeys::A);
	InputConfig.Add(EInputConfig::InputConfig_Right, EKeys::D);
	InputConfig.Add(EInputConfig::InputConfig_Up, EKeys::W);
	InputConfig.Add(EInputConfig::InputConfig_LightPunche, EKeys::J);
	InputConfig.Add(EInputConfig::InputConfig_HeavyPunche, EKeys::K);
	InputConfig.Add(EInputConfig::InputConfig_LightKick, EKeys::U);
	InputConfig.Add(EInputConfig::InputConfig_HeavyKick, EKeys::I);
}


// Called when the game starts
void UFightCoreComponent::BeginPlay()
{
	Super::BeginPlay();

	MeshComponentRef = Cast<USkeletalMeshComponent>(GetOwner()->GetComponentByClass(USkeletalMeshComponent::StaticClass()));

	if (MeshComponentRef)
	{
		InputComponentRef = Cast<UInputComponent>(GetOwner()->GetComponentByClass(UInputComponent::StaticClass()));
		BindInput();
	}

}

void UFightCoreComponent::MapInput()
{
	check(InputComponentRef);

	InputData = (uint8)EInputConfig::InputConfig_None;

	for (const EInputConfig& inputConfig : InputCheck)
	{
		if (!InputConfig.Find(inputConfig))
			continue;

		auto InputKey = InputConfig.FindRef(inputConfig);
		float AxisKeyValue = InputComponentRef->GetAxisKeyValue(InputKey);
		if (AxisKeyValue >= 1)
		{
			InputData |= (uint8)inputConfig;
		}
	}

	if (InputData & (uint8)EInputConfig::InputConfig_Down &&
		InputData & (uint8)EInputConfig::InputConfig_Up )
	{
		InputData &= ~((uint8)EInputConfig::InputConfig_Down | (uint8)EInputConfig::InputConfig_Up);
	}

	if (InputData & (uint8)EInputConfig::InputConfig_Left &&
		InputData & (uint8)EInputConfig::InputConfig_Right)
	{
		InputData &= ~((uint8)EInputConfig::InputConfig_Left | (uint8)EInputConfig::InputConfig_Right);
	}
}

void UFightCoreComponent::BindInput()
{
	check(InputComponentRef);

	for (const EInputConfig& inputConfig : InputCheck)
	{
		if (!InputConfig.Find(inputConfig))
			continue;

		const FKey& key = InputConfig.FindRef(inputConfig);

		InputComponentRef->BindAxisKey(key);

#if WITH_EDITOR
		GEngine->AddOnScreenDebugMessage(
			-1,
			5,
			FColor::Green,
			FString::Printf(TEXT("Bind %s"),*key.ToString())
		);
#endif // WITH_EDITOR
	}
}

// Called every frame
void UFightCoreComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	MapInput();

#if WITH_EDITOR

	char output[9];
	itoa((int)InputData, output, 2);

	auto outstring = FString(output);
	int loop = 9 - outstring.Len();

	FString out;
	for (int i = 0; i < loop; i++)
	{
		out += "0";
	}


	GEngine->AddOnScreenDebugMessage(
		-1,
		0,
		FColor::Green,
		TEXT("InputData:") + out + outstring
		);
#endif // WITH_EDITOR
}

