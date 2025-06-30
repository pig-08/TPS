// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTask_FindPatrollLocation.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindPatrollLocation::UBTTask_FindPatrollLocation()
{
	NodeName = TEXT("FindPatrol");
}

EBTNodeResult::Type UBTTask_FindPatrollLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (nullptr == ControllingPawn)
		return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if (nullptr == NavSystem)
		return EBTNodeResult::Failed;

	FVector Origin = ControllingPawn->GetActorLocation();
	FNavLocation NaxtPatrolLocation;

	if (NavSystem->GetRandomPointInNavigableRadius(Origin, PatrolRadius, NaxtPatrolLocation))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(PatrolLocationKey.SelectedKeyName, NaxtPatrolLocation.Location);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;


}
