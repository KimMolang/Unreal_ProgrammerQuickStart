// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FPSProjectile.generated.h"

UCLASS()
class QUICKSTART_API AFPSProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;

	// 프로젝타일의 속도를 발사 방향으로 초기화시키는 함수입니다.
	void FireInDirection(const FVector& ShootDirection);

	// 프로젝타일이 무언가에 맞으면 호출되는 함수입니다.
	void OnHit(UPrimitiveComponent* HitComponent
		, AActor* OtherActor, UPrimitiveComponent* OtherComponent
		, FVector NormalImpulse, const FHitResult& Hit);
};
