// Fill out your copyright notice in the Description page of Project Settings.

#include "QuickStart.h"
#include "FPSProjectGameMode.h"


void AFPSProjectGameMode::StartPlay()
{
	Super::StartPlay();

	if (GEngine)
	{
		// ����� �޽����� 5 �ʰ� ǥ���մϴ�.
		// "Ű" (ù ��° �μ�) ���� -1 �� �ϸ�
		// �� �޽����� ���� ������Ʈ�ϰų� ���ΰ�ĥ �ʿ䰡 ������ ��Ÿ���ϴ�.
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World!"));
		//UE_LOG(LogClass, Log, TEXT("You have collected %s"), TEXT("!!"));
	}
}

