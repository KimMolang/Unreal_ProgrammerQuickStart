// Fill out your copyright notice in the Description page of Project Settings.

#include "QuickStart.h"
#include "FPSProjectile.h"


// Sets default values
AFPSProjectile::AFPSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	{
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
		CollisionComponent->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnHit);
		CollisionComponent->InitSphereRadius(15.0f);

		RootComponent = CollisionComponent;
	}


	// 현재 블루프린트에서
	// ProjectileMeshComponent 의 콜리전 프리셋 값을 NoCollision 으로 설정했다.
	// 콜리전에 이 스태틱 메시가 아닌 SphereComponent 를 사용하기 때문이다.
	{
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = 3000.0f;
		ProjectileMovementComponent->MaxSpeed = 3000.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness = 0.3f;
	}

	// 3 초 후 죽습니다.
	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// 프로젝타일의 속도를 발사 방향으로 초기화시키는 함수입니다.
void AFPSProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity
		= ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

// 프로젝타일에 무언가 맞으면 호출되는 함수입니다.
// CollisionComponent->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnHit);
void AFPSProjectile::OnHit(UPrimitiveComponent* HitComponent
	, AActor* OtherActor, UPrimitiveComponent* OtherComponent
	, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(
			ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
	}
}