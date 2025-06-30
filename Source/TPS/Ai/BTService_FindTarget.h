// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_FindTarget.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API UBTService_FindTarget : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_FindTarget();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere)
	float FindRadius = 500.0f;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetActorKey;
	
};
