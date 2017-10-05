// Fill out your copyright notice in the Description page of Project Settings.

#include "QuickStart.h"
#include "CollidingPawn.h"

#include "CollidingPawnMovementComponent.h"


// Sets default values
ACollidingPawn::ACollidingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 물리 월드와의 상호작용을 위한 Sphere 컴포넌트
	// 콜리전 모양을 시각적으로 나타내 줄 Static Mesh 컴포넌트
	// 마음대로 켜고 끌 수 있는 Particle System 컴포넌트
	// (+Spring Arm 컴포넌트)

	// 1. Sphere Component
	// Character(Actor)를 상속 받으면 기본적으로 다 있지만
	// Pawn은 없는 모양
	USphereComponent* SphereComponent
		= CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0f);
	// 유니티의 충돌 오브젝트 태그 네임 같은 거 일 듯
	// 전에 프로젝트 설정 창에서 하나 추가해서 블루프린트 에디터에서
	// 콜리젼 프리셋값 넣어준 거와 비슷하지 않을까?
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));
	

	// 2. Static Mesh Component
	UStaticMeshComponent* SphereVisual
		= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetupAttachment(RootComponent);
	// 에셋 읽기
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(
		TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		// 그냥 구체를 충돌체 위치랑 맞춰줄라고 이 난리 치는 거
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		SphereVisual->SetWorldScale3D(FVector(0.8f));
	}
	// ** 코드로 스태틱 메시 애셋의 위치를 확인할 수는 있지만,
	// 애셋 경로를 하드코딩하는 것은 별로 바람직한 애셋 로드 방식이 아닙니다.
	// 클래스에서 컴포넌트 를 사용한다면 보통은 코드로 컴포넌트 자체를 만든 다음,
	// 언리얼 에디터 에서 선택하는 것이 낫습니다.
	// 물론 이 작업은 코드에서 바로 할 수도 있으며,
	// 새로운 기능을 만들거나 디버깅을 하는 프로그래머에게는 더 빠를 수도 있습니다.


	// 3. Particle System Component
	// 활성화 또는 비활성화시킬 수 있는 파티클 시스템 생성
	OurParticleSystem
		= CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	OurParticleSystem->SetupAttachment(SphereVisual);
	OurParticleSystem->bAutoActivate = false;
	OurParticleSystem->SetRelativeLocation(FVector(-20.0f, 0.0f, 20.0f));
	// 에셋 읽기
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(
		TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
	if (ParticleAsset.Succeeded())
	{
		OurParticleSystem->SetTemplate(ParticleAsset.Object);
	}


	// 4. Spring Arm Component
	// 스프링 암을 사용하여 카메라에 부드럽고 자연스러운 모션을 적용합니다.
	USpringArmComponent* SpringArm
		= CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->RelativeRotation = FRotator(-45.f, 0.f, 0.f);
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->bEnableCameraLag = true;	// 카메라를 부드럽게 이동
	SpringArm->CameraLagSpeed = 3.0f;	// 이동 스피드

	// 카메라를 만들어 스프링 암에 붙입니다.
	// 실제 Camera 컴포넌트는 만들기도 쉽고,
	// 별도의 세팅도 필요치 않습니다. Spring Arm 에는 소켓 이 내장되어 있어,
	// 베이스가 아닌 이 곳에 붙일 수 있습니다.
	UCameraComponent* Camera
		= CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	// 컴포넌트를 만들어 붙였으니,
	// 이 폰 을 기본 플레이어가 조종하도록 설정해 줘야 합니다.
	AutoPossessPlayer = EAutoReceiveInput::Player0;	// 기본 플레이어 콘트롤 획득


	// 새로 커스텀한 UCollidingPawnMovementComponent 셋팅
	// 이 컴포넌트 는 우리 컴포넌트 계층구조에 붙일 필요가 없습니다.
	// 왜냐면 우리 컴포넌트 는 모두 씬 컴포넌트 유형이었는데,
	// 애초부터 물리적 위치가 필요한 것들이기 때문입니다.
	// 하지만 Movement Controller 는 씬 컴포넌트 가 아니라,
	// 물리적 오브젝트를 나타내지 않기에, 물리적 위치에 존재한다든가
	// 다른 컴포넌트 에 물리적으로 붙인다든가 하는 개념은 적용되지 않습니다.
	OurMovementComponent
		= CreateDefaultSubobject<UCollidingPawnMovementComponent>(TEXT("CustomMovementComponent"));
	OurMovementComponent->UpdatedComponent = RootComponent;	// 루트를 업데이트 하세요
}

// Called when the game starts or when spawned
void ACollidingPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollidingPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ACollidingPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("MoveX", this, &ACollidingPawn::MoveForward);
	InputComponent->BindAxis("MoveY", this, &ACollidingPawn::MoveRight);
	InputComponent->BindAxis("Turn", this, &ACollidingPawn::Turn);

	InputComponent->BindAction("ParticleToggle", IE_Pressed, this, &ACollidingPawn::ParticleToggle);

}

UPawnMovementComponent* ACollidingPawn::GetMovementComponent() const
{
	return OurMovementComponent;
}

void ACollidingPawn::MoveForward(const float _fAxisValue)
{
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorForwardVector() * _fAxisValue);
	}
}

void ACollidingPawn::MoveRight(const float _fAxisValue)
{
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorRightVector() * _fAxisValue);
	}
}

void ACollidingPawn::Turn(const float _fAxisValue)
{
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += _fAxisValue;
	SetActorRotation(NewRotation);
}

void ACollidingPawn::ParticleToggle()
{
	if (OurParticleSystem && OurParticleSystem->Template)
	{
		OurParticleSystem->ToggleActive();
	}
}