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
	// �߻� ó��
	UFUNCTION()
	void OnFire();

public :
	// ī�޶� ��ġ������ �ѱ� ������
	// BlueprintReadWrite �����ڸ� ���ؼ��� �������Ʈ �ȿ���
	// �ѱ� �������� ���� ���ϰ� ������ �� �ֽ��ϴ�. 
	// �������Ʈ�� ���� �� �ʿ�� ����̴µ� Ʃ�丮�󿡼��� ���� �ִ�.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	// ������ų ������Ÿ�� Ŭ����
	// EditDefaultsOnly �����ڴ� ������Ÿ�� Ŭ������ �������Ʈ�� �� �ν��Ͻ� �󿡼��� �ƴ϶�
	// �������Ʈ�� ����Ʈ�θ� ������ �� �ִٴ� ���Դϴ�. 
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AFPSProjectile> ProjectileClass;
};
