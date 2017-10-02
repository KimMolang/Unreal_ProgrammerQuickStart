// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Countdown.generated.h"

UCLASS()
class QUICKSTART_API ACountdown : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACountdown();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
	int32 CountdownTime;
	UTextRenderComponent* CountdownText;

	void AdvanceTimer();
	void UpdateTimerDisplay();

	
	/*
	BlueprintCallable �Լ��� C++ �� �ۼ��Ǿ� �������Ʈ �׷��� ���� ȣ�� ����������, C++ �ڵ� ���� ���̴� �����̳� ����Ⱑ �Ұ����մϴ�. �̷� ������ ��ŷ�� �Լ��� ���α׷��Ӱ� �ƴ� ����� ������ ���α׷��ֵ� ��������, ������ �ؼ��� �ȵǰų� �����ϴ� ���� �ٶ������� ���� ����Դϴ�. ���� ������ ���� �Լ��� �� �� �ֽ��ϴ�.
	BlueprintImplementableEvent �Լ��� C++ ��� (.h) ���Ͽ� �����ǳ�, �Լ� ������ C++ �� �ƴ� �������� �������Ʈ �׷��� ���� �ۼ��Ǵ� ���Դϴ�. �̴� ���� ���α׷��Ӱ� �ƴ� ������� ����� �⺻ �����̳� ǥ�� ������ ���� Ư�� ��Ȳ�� ���� ������ �Ը���� ���� �� �ִ� �ɷ��� �ֱ� ���� ���Դϴ�. �̿� ���� �����δ� ���ּ� ���ӿ��� �÷��̾��� ���ּ��� �Ŀ����� �Ծ��� �� �߻��ϴ� �̺�Ʈ���� ���� �� �� �ֽ��ϴ�.
	BlueprintNativeEvent �Լ��� BlueprintCallable �� BlueprintImplementableEvent �Լ��� ������ �� ���� ���Դϴ�. C++ �� �⺻ �۵������ ���α׷��ֵǾ� ������, �������Ʈ �׷��� �� ����Ἥ ���� �Ǵ� ��ü �����մϴ�. �̿� ���� ���α׷����� �� �� C++ �ڵ�� �Ʒ�ó�� �׻� �̸� ���� "_Implementation" �� �ٴ� ���� �Լ��� ���ϴ�. ���� ������ �ɼ��̹Ƿ�, �� Ʃ�丮�󿡼��� �� �ɼ��� ����ϰڽ��ϴ�.
	*/
	UFUNCTION(BlueprintNativeEvent)
	void CountdownHasFinished();
	virtual void CountdownHasFinished_Implementation();

	
	FTimerHandle CountdownTimerHandle;
};
