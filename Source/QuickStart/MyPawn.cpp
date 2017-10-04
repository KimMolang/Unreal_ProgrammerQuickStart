// Fill out your copyright notice in the Description page of Project Settings.

#include "QuickStart.h"
#include "MyPawn.h"


// Sets default values
AMyPawn::AMyPawn()
	: CurrentVelocity(0.0f)
	, CurrentPlusVelocity(0.0f)

	, bGrowing(false)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// 무언가를 붙일 더미 루트 컴포넌트
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	UCameraComponent* OurCamera
		= CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurVisibleComponent
		= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));

	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FVector(250.0f, 0.0f, 250.0f));
	OurCamera->SetRelativeRotation(FRotator(0.0f, -45.0f, -180.0f));

	OurVisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	{
		float CurrentScale = OurVisibleComponent->GetComponentScale().X;

		if (bGrowing)
		{
			CurrentScale += DeltaTime;
			CurrentPlusVelocity.X += 200.0f;
		}
		else
		{
			CurrentScale -= DeltaTime * 0.5f;
			CurrentPlusVelocity.X = 0.0f;
		}

		CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
		OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale));
	}
	
	{
		if (!CurrentVelocity.IsZero())
		{
			FVector NewLocation = GetActorLocation()
				+ ((CurrentVelocity + CurrentPlusVelocity) * DeltaTime);
			SetActorLocation(NewLocation);
		}
	}
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("Grow", IE_Pressed, this, &AMyPawn::StartGrowing);
	InputComponent->BindAction("Grow", IE_Released, this, &AMyPawn::StopGrowing);

	InputComponent->BindAxis("MoveX", this, &AMyPawn::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &AMyPawn::Move_YAxis);
}

void AMyPawn::Move_XAxis(const float _fAxisValue)
{
	CurrentVelocity.X = FMath::Clamp(_fAxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMyPawn::Move_YAxis(const float _fAxisValue)
{
	CurrentVelocity.Y = FMath::Clamp(_fAxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMyPawn::StartGrowing()
{
	bGrowing = true;
}

void AMyPawn::StopGrowing()
{
	bGrowing = false;
}