// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "FPSProjectGameMode.generated.h"

/**
 * 
 */
UCLASS()
class QUICKSTART_API AFPSProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	
	virtual void StartPlay() override;
};
