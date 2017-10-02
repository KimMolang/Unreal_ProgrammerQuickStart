// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CameraDirecto.generated.h"

UCLASS()
class QUICKSTART_API ACameraDirecto : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraDirecto();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	//UPROPERTY(EditAnywhere)
	//AActor* CameraOne;

	//UPROPERTY(EditAnywhere)
	//AActor* CameraTwo;

	UPROPERTY(EditAnywhere)
	TArray<AActor*>	arrCamera;

	int32	CurCameraIndex;

	float	TimeToNextCameraChange;
};
