// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/EnemyAiController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

AEnemyAiController::AEnemyAiController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAsserRef(TEXT("/Script/AIModule.BlackboardData'/Game/Ai/BB_Enemy.BB_Enemy'"));

	if (BBAsserRef.Succeeded())
	{
		BBAsset = BBAsserRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef(TEXT("/Script/AIModule.BehaviorTree'/Game/Ai/BT_Enemy.BT_Enemy'"));

	if (BTAssetRef.Succeeded())
	{
		BTAsset = BTAssetRef.Object;
	}
}

void AEnemyAiController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAi();
}

void AEnemyAiController::RunAi()
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();
	if (UseBlackboard(BBAsset, BlackboardPtr))
	{
		bool RunResult = RunBehaviorTree(BTAsset);
		ensure(RunResult);
	}
}

void AEnemyAiController::StopAi()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTComponent)
	{
		BTComponent->StopTree();
	}
}
