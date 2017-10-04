// Fill out your copyright notice in the Description page of Project Settings.

#include "QuickStart.h"
#include "FPSCharacter.h"

#include "FPSProjectile.h"


// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	{
		FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
		FPSCameraComponent->SetupAttachment(GetCapsuleComponent());

		// 카메라 위치를 눈 살짝 위쪽으로 잡습니다.
		FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));

		// 폰의 카메라 로테이션 제어를 허용합니다.
		FPSCameraComponent->bUsePawnControlRotation = true;
	}

	// 손 메쉬
	{
		FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
		// 소유 플레이어만 이 메시를 볼 수 있습니다.
		// 이 Character 를 빙의한 PlayerController 에게만 보임을 나타냅니다.
		FPSMesh->SetOnlyOwnerSee(true);
		// FPS 메시를 FPS 카메라에 붙입니다.
		FPSMesh->SetupAttachment(FPSCameraComponent);
		// 일부 환경 섀도잉을 꺼 메시가 하나인 듯 보이는 느낌을 유지합니다.
		FPSMesh->bCastDynamicShadow = false;
		FPSMesh->CastShadow = false;
	}

	GetMesh()->SetOwnerNoSee(true);
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red
			, TEXT("We are using FPSCharacter."));
	}
}

// Called every frame
void AFPSCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveX", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveY", this, &AFPSCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::StopJump);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::OnFire);
}

void AFPSCharacter::MoveForward(const float _fAxisValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, _fAxisValue);

}

void AFPSCharacter::MoveRight(const float _fAxisValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, _fAxisValue);
}

void AFPSCharacter::StartJump()
{
	bPressedJump = true;
}

void AFPSCharacter::StopJump()
{
	bPressedJump = false;
}

void AFPSCharacter::OnFire()
{
	if (ProjectileClass == nullptr)
		return;


	// 카메라 트랜스폼을 구합니다.
	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);

	// MuzzleOffset 을 카메라 스페이스에서 월드 스페이스로 변환합니다.
	FVector MuzzleLocation = CameraLocation							// 2. 현 카메라 위치를 더한다
		+ FTransform(CameraRotation).TransformVector(MuzzleOffset);	// 1. 카메라 방향에 따른 총알 위치에
	FRotator MuzzleRotation = CameraRotation;
	// 조준을 약간 윗쪽으로 올려줍니다.
	MuzzleRotation.Pitch += 10.0f;

	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;
		
		AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(
			ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);

		if (Projectile)
		{
			FVector LaunchDirection = MuzzleRotation.Vector();
			Projectile->FireInDirection(LaunchDirection);
		}
	}
}