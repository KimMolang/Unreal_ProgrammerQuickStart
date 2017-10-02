// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CameraDirecto.generated.h"

// Atomic 하면 에디터에서 멤버 변수들 셋팅이 안 됨!!
USTRUCT(/*Atomic*/)
struct FCameraBlendEffect
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	AActor*		Camera;
	UPROPERTY(EditAnywhere)
	float		TimeBetweenCameraChange;
	UPROPERTY(EditAnywhere)
	float		SmoothBlendTime;

	FCameraBlendEffect()
		: Camera(nullptr)
		, TimeBetweenCameraChange(0.0f)
		, SmoothBlendTime(0.0f) {}
};

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


	UPROPERTY(EditAnywhere)
	TArray<FCameraBlendEffect> arrCameraEffect;

	int32	CurCameraIndex;
	float	TimeToNextCameraChange;
};
