// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PawnMovementComponent.h"
#include "CollidingPawnMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class QUICKSTART_API UCollidingPawnMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()
	
public:
	//UPawnMovementComponent::TickComponent ¸¦ override!
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType
		, FActorComponentTickFunction *ThisTickFunction) override;
};
