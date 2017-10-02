// Fill out your copyright notice in the Description page of Project Settings.

#include "QuickStart.h"
#include "CameraDirecto.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
ACameraDirecto::ACameraDirecto()
: CurCameraIndex(0)
, TimeToNextCameraChange(0.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACameraDirecto::BeginPlay()
{
	Super::BeginPlay();
	
	// Set Base Camera
	APlayerController* OutPlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if (OutPlayerController != nullptr
		&& arrCameraEffect.IsValidIndex(CurCameraIndex)
		&& arrCameraEffect[CurCameraIndex].Camera != nullptr )
	{
		OutPlayerController->SetViewTarget(arrCameraEffect[CurCameraIndex].Camera);
		TimeToNextCameraChange = arrCameraEffect[CurCameraIndex].TimeBetweenCameraChange;
	}
}

// Called every frame
void ACameraDirecto::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );


	TimeToNextCameraChange -= DeltaTime;

	if (TimeToNextCameraChange <= 0.0f)
	{
		++CurCameraIndex;

		if (CurCameraIndex >= arrCameraEffect.Num())
		{
			CurCameraIndex = 0;
		}

		// 로컬 플레이어의 컨트롤을 처리하는 액터를 찾습니다.
		APlayerController* OutPlayerController = UGameplayStatics::GetPlayerController(this, 0);

		if (OutPlayerController == nullptr)
			return;


		if (arrCameraEffect.IsValidIndex(CurCameraIndex) == false
			|| arrCameraEffect[CurCameraIndex].Camera == nullptr)
			return;

		OutPlayerController->SetViewTargetWithBlend(
			arrCameraEffect[CurCameraIndex].Camera
			, arrCameraEffect[CurCameraIndex].SmoothBlendTime);
		TimeToNextCameraChange = arrCameraEffect[CurCameraIndex].TimeBetweenCameraChange;
	}
}

