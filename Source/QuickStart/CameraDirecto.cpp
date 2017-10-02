// Fill out your copyright notice in the Description page of Project Settings.

#include "QuickStart.h"
#include "CameraDirecto.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
ACameraDirecto::ACameraDirecto()
: CurCameraIndex(0)
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
		&& arrCamera.IsValidIndex(CurCameraIndex)
		&& arrCamera[CurCameraIndex] != nullptr )
	{
		OutPlayerController->SetViewTarget(arrCamera[CurCameraIndex]);
	}
}

// Called every frame
void ACameraDirecto::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	const float TimeBetweenCameraChange	= 2.0f;
	const float SmoothBlendTime = 0.75f;

	//if (CameraOne == nullptr || CameraTwo == nullptr)
	//	return;


	TimeToNextCameraChange -= DeltaTime;

	if (TimeToNextCameraChange <= 0.0f)
	{
		TimeToNextCameraChange = TimeBetweenCameraChange;

		++CurCameraIndex;

		if (CurCameraIndex >= arrCamera.Num())
		{
			CurCameraIndex = 0;
		}

		// 로컬 플레이어의 컨트롤을 처리하는 액터를 찾습니다.
		APlayerController* OutPlayerController = UGameplayStatics::GetPlayerController(this, 0);

		if (OutPlayerController == nullptr)
			return;

		//if (OutPlayerController->GetViewTarget() != CameraOne)
		//{
		//	OutPlayerController->SetViewTarget(CameraOne);
		//}
		//else if (OutPlayerController->GetViewTarget() != CameraTwo)
		//{
		//	OutPlayerController->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);
		//}


		if (arrCamera.IsValidIndex(CurCameraIndex) == false
			|| arrCamera[CurCameraIndex] == nullptr)
			return;

		OutPlayerController->SetViewTargetWithBlend(arrCamera[CurCameraIndex], SmoothBlendTime);
	}
}

