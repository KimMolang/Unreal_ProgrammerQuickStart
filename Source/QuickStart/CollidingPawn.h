// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "CollidingPawn.generated.h"

UCLASS()
class QUICKSTART_API ACollidingPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACollidingPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	
public :
	UParticleSystemComponent*				OurParticleSystem;
	class UCollidingPawnMovementComponent*	OurMovementComponent;

public :	// 새로 만든 UPawnMovementComponent 를 리던한다
	virtual UPawnMovementComponent* GetMovementComponent() const override;

public :
	void MoveForward(const float _fAxisValue);
	void MoveRight(const float _fAxisValue);

	void Turn(const float _fAxisValue);
	void ParticleToggle();

protected :
	USpringArmComponent* OurCameraSpringArm;
	UCameraComponent* OurCamera;

	FVector2D	MovementInput;
	FVector2D	CameraInput;
	float		ZoomFactor;
	bool		bZoomingIn;

	void PitchCamera(const float _fAxisValue);
	void YawCamera(const float _fAxisValue);

	void ZoomIn();
	void ZoomOut();
};
