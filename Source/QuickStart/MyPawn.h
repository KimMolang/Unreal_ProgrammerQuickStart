// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class QUICKSTART_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	
public :
	UPROPERTY(EditAnywhere)
	USceneComponent* OurVisibleComponent;

private :
	void	Move_XAxis(const float _fAxisValue);
	void	Move_YAxis(const float _fAxisValue);

	void	StartGrowing();
	void	StopGrowing();

	FVector CurrentVelocity;
	FVector CurrentPlusVelocity;

	bool	bGrowing;
};
