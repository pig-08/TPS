// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTService_FindTarget.h"
#include "AIController.h"
#include "BehaviorTree//BlackboardComponent.h"
#include "Engine/OverlapResult.h"

UBTService_FindTarget::UBTService_FindTarget()
{
	NodeName = TEXT("FindTarget");
	Interval = 0.5f;
}

void UBTService_FindTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (nullptr == ControllingPawn)
		return;

	UWorld* World = ControllingPawn->GetWorld();

	if (nullptr == World)
		return;

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(ControllingPawn);
	FVector Location = ControllingPawn->GetActorLocation();
		 

	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Location,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(FindRadius),
		CollisionQueryParams
	);

	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			APawn* TargetPawn = Cast<APawn>(OverlapResult.GetActor());
			if (TargetPawn && TargetPawn->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(TargetActorKey.SelectedKeyName, TargetPawn);

				DrawDebugSphere(World, Location, FindRadius, 16, FColor::Green, false, 0.2f);
				return;
			}
		}
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TargetActorKey.SelectedKeyName, nullptr);
	DrawDebugSphere(World, Location, FindRadius, 16, FColor::Red, false, 0.2f);
}
