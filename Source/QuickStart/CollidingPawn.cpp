// Fill out your copyright notice in the Description page of Project Settings.

#include "QuickStart.h"
#include "CollidingPawn.h"

#include "CollidingPawnMovementComponent.h"


// Sets default values
ACollidingPawn::ACollidingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ���� ������� ��ȣ�ۿ��� ���� Sphere ������Ʈ
	// �ݸ��� ����� �ð������� ��Ÿ�� �� Static Mesh ������Ʈ
	// ������� �Ѱ� �� �� �ִ� Particle System ������Ʈ
	// (+Spring Arm ������Ʈ)

	// 1. Sphere Component
	// Character(Actor)�� ��� ������ �⺻������ �� ������
	// Pawn�� ���� ���
	USphereComponent* SphereComponent
		= CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0f);
	// ����Ƽ�� �浹 ������Ʈ �±� ���� ���� �� �� ��
	// ���� ������Ʈ ���� â���� �ϳ� �߰��ؼ� �������Ʈ �����Ϳ���
	// �ݸ��� �����°� �־��� �ſ� ������� ������?
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));
	

	// 2. Static Mesh Component
	UStaticMeshComponent* SphereVisual
		= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetupAttachment(RootComponent);
	// ���� �б�
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(
		TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		// �׳� ��ü�� �浹ü ��ġ�� �����ٶ�� �� ���� ġ�� ��
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		SphereVisual->SetWorldScale3D(FVector(0.8f));
	}
	// ** �ڵ�� ����ƽ �޽� �ּ��� ��ġ�� Ȯ���� ���� ������,
	// �ּ� ��θ� �ϵ��ڵ��ϴ� ���� ���� �ٶ����� �ּ� �ε� ����� �ƴմϴ�.
	// Ŭ�������� ������Ʈ �� ����Ѵٸ� ������ �ڵ�� ������Ʈ ��ü�� ���� ����,
	// �𸮾� ������ ���� �����ϴ� ���� �����ϴ�.
	// ���� �� �۾��� �ڵ忡�� �ٷ� �� ���� ������,
	// ���ο� ����� ����ų� ������� �ϴ� ���α׷��ӿ��Դ� �� ���� ���� �ֽ��ϴ�.


	// 3. Particle System Component
	// Ȱ��ȭ �Ǵ� ��Ȱ��ȭ��ų �� �ִ� ��ƼŬ �ý��� ����
	OurParticleSystem
		= CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	OurParticleSystem->SetupAttachment(SphereVisual);
	OurParticleSystem->bAutoActivate = false;
	OurParticleSystem->SetRelativeLocation(FVector(-20.0f, 0.0f, 20.0f));
	// ���� �б�
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(
		TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
	if (ParticleAsset.Succeeded())
	{
		OurParticleSystem->SetTemplate(ParticleAsset.Object);
	}


	// 4. Spring Arm Component
	// ������ ���� ����Ͽ� ī�޶� �ε巴�� �ڿ������� ����� �����մϴ�.
	USpringArmComponent* SpringArm
		= CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->RelativeRotation = FRotator(-45.f, 0.f, 0.f);
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->bEnableCameraLag = true;	// ī�޶� �ε巴�� �̵�
	SpringArm->CameraLagSpeed = 3.0f;	// �̵� ���ǵ�

	// ī�޶� ����� ������ �Ͽ� ���Դϴ�.
	// ���� Camera ������Ʈ�� ����⵵ ����,
	// ������ ���õ� �ʿ�ġ �ʽ��ϴ�. Spring Arm ���� ���� �� ����Ǿ� �־�,
	// ���̽��� �ƴ� �� ���� ���� �� �ֽ��ϴ�.
	UCameraComponent* Camera
		= CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	// ������Ʈ�� ����� �ٿ�����,
	// �� �� �� �⺻ �÷��̾ �����ϵ��� ������ ��� �մϴ�.
	AutoPossessPlayer = EAutoReceiveInput::Player0;	// �⺻ �÷��̾� ��Ʈ�� ȹ��


	// ���� Ŀ������ UCollidingPawnMovementComponent ����
	// �� ������Ʈ �� �츮 ������Ʈ ���������� ���� �ʿ䰡 �����ϴ�.
	// �ֳĸ� �츮 ������Ʈ �� ��� �� ������Ʈ �����̾��µ�,
	// ���ʺ��� ������ ��ġ�� �ʿ��� �͵��̱� �����Դϴ�.
	// ������ Movement Controller �� �� ������Ʈ �� �ƴ϶�,
	// ������ ������Ʈ�� ��Ÿ���� �ʱ⿡, ������ ��ġ�� �����Ѵٵ簡
	// �ٸ� ������Ʈ �� ���������� ���δٵ簡 �ϴ� ������ ������� �ʽ��ϴ�.
	OurMovementComponent
		= CreateDefaultSubobject<UCollidingPawnMovementComponent>(TEXT("CustomMovementComponent"));
	OurMovementComponent->UpdatedComponent = RootComponent;	// ��Ʈ�� ������Ʈ �ϼ���
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