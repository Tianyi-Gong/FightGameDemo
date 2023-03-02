// Fill out your copyright notice in the Description page of Project Settings.


#include "FightActionInputTrigger.h"

UFightActionInputTrigger::UFightActionInputTrigger():
	CurrentCheckInputIndex(0)
{

}

void UFightActionInputTrigger::ReciveInput(EInputConfig InputConfig, bool& bMapResult)
{

}

void UFightActionInputTrigger::PostLoad()
{
	if (CheckInputConfig.Num() == 0)
		return;
	
	CurrentCheckInputConfig = CheckInputConfig[CurrentCheckInputIndex];
}
