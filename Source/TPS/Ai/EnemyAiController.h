// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAiController.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API AEnemyAiController : public AAIController
{
	GENERATED_BODY()
public:
	AEnemyAiController();

public:
	virtual void OnPossess(APawn* InPawn) override;
public:
	void RunAi();
	void StopAi();

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBlackboardData> BBAsset;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBehaviorTree> BTAsset;
};
