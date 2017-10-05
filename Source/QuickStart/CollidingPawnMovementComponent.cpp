// Fill out your copyright notice in the Description page of Project Settings.

#include "QuickStart.h"
#include "CollidingPawnMovementComponent.h"


void UCollidingPawnMovementComponent::TickComponent(
	float DeltaTime, enum ELevelTick TickType
	, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ��� ���� ���� ��ȿ����, �̵� �������� Ȯ���մϴ�.
	if (PawnOwner == nullptr || UpdatedComponent == nullptr
		|| ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	// ACollidingPawn::Tick �� ������ �����Ʈ ���͸� ��(�� �� �Ұ�)�մϴ�.
	FVector DesiredMovementThisFrame
		= ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 150.0f;
	// ConsumeInputVector �� �̵� �Է��� �����ϴ� �� ����� ���� ���� ���� ���� �� �Ұ��մϴ�.

	if (!DesiredMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovementThisFrame
			, UpdatedComponent->GetComponentRotation(), true, Hit);
		// SafeMoveUpdatedComponent �� �𸮾� ���� �������� ����Ͽ�
		// ��ü ��ֹ��� ���� Pawn Movement Component �� �̵���ŵ�ϴ�. 

		// ���𰡿� �ε�������, ���ư� ���ϴ�.
		if (Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
			// SlideAlongSurface �� �̵��ϴٰ� �浹 �߻���
			// �׳� ���ڸ��� ���� ���̳� ���ο� "�޶�ٱ�" ���ٴ�,
			// �� ǥ���� Ÿ�� �ε巴�� �̲��������� �ϴ� �� ���õ� ���� ��� ó���� �մϴ�.
		}
	}

	/*
	Pawn Movement Components ���� ������ ���� ����� �� ������,
	�� Ʃ�丮�� �������� �ʿ�ġ �ʽ��ϴ�.
	Floating Pawn Movement, Spectator Pawn Movement, Character Movement Component ����
	�ٸ� Ŭ������ ���캸�� �߰����� ��ʳ� ������ ã�ƺ� �� �ֽ��ϴ�.
	*/
};