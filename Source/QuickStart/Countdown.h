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
	BlueprintCallable 함수는 C++ 로 작성되어 블루프린트 그래프 에서 호출 가능하지만, C++ 코드 편집 없이는 변경이나 덮어쓰기가 불가능합니다. 이런 식으로 마킹된 함수는 프로그래머가 아닌 사람이 쓰도록 프로그래밍된 것이지만, 변경을 해서는 안되거나 변경하는 것이 바람직하지 않은 경우입니다. 쉬운 예제로 수학 함수를 들 수 있습니다.
	BlueprintImplementableEvent 함수는 C++ 헤더 (.h) 파일에 구성되나, 함수 본문은 C++ 가 아닌 전적으로 블루프린트 그래프 에서 작성되는 것입니다. 이는 보통 프로그래머가 아닌 사람에게 예상된 기본 동작이나 표준 동작이 없는 특수 상황에 대한 반응을 입맛대로 만들 수 있는 능력을 주기 위해 쓰입니다. 이에 대한 예제로는 우주선 게임에서 플레이어의 우주선이 파워업을 먹었을 때 발생하는 이벤트같은 것을 들 수 있습니다.
	BlueprintNativeEvent 함수는 BlueprintCallable 과 BlueprintImplementableEvent 함수를 조합한 것 같은 것입니다. C++ 로 기본 작동방식이 프로그래밍되어 있지만, 블루프린트 그래프 로 덮어써서 보조 또는 대체 가능합니다. 이에 대한 프로그래밍을 할 때 C++ 코드는 아래처럼 항상 이름 끝에 "_Implementation" 이 붙는 가상 함수에 들어갑니다. 가장 유연한 옵션이므로, 이 튜토리얼에서는 이 옵션을 사용하겠습니다.
	*/
	UFUNCTION(BlueprintNativeEvent)
	void CountdownHasFinished();
	virtual void CountdownHasFinished_Implementation();

	
	FTimerHandle CountdownTimerHandle;
};
