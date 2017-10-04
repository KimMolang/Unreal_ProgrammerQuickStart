// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

UCLASS()
class QUICKSTART_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
private :
	UFUNCTION()
	void	MoveForward(const float _fAxisValue);
	UFUNCTION()
	void	MoveRight(const float _fAxisValue);

	UFUNCTION()
	void StartJump();

	UFUNCTION()
	void StopJump();

public :
	//UPROPERTY(EditAnywhere)
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FPSMesh;


public :
	// 발사 처리
	UFUNCTION()
	void OnFire();

public :
	// 카메라 위치에서의 총구 오프셋
	// BlueprintReadWrite 지정자를 통해서는 블루프린트 안에서
	// 총구 오프셋의 값을 구하고 설정할 수 있습니다. 
	// 블루프린트로 딱히 뺄 필요는 없어보이는데 튜토리얼에서는 빼고 있다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	// 스폰시킬 프로젝타일 클래스
	// EditDefaultsOnly 지정자는 프로젝타일 클래스를 블루프린트의 각 인스턴스 상에서가 아니라
	// 블루프린트의 디폴트로만 설정할 수 있다는 뜻입니다. 
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AFPSProjectile> ProjectileClass;
};
