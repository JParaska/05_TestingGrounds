// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolRoute.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();

	// Get waypoints	
	auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return EBTNodeResult::Failed;

	auto ControlledPawn = Controller->GetPawn();
	if (!ControlledPawn) return EBTNodeResult::Failed;

	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();
	if (!PatrolRoute) return EBTNodeResult::Failed;

	auto Waypoints = PatrolRoute->GetWaypoints();
	if (Waypoints.Num() == 0) {
		UE_LOG(LogTemp, Warning, TEXT("A guard %s is missing patrol points."), *ControlledPawn->GetName());
		return EBTNodeResult::Failed;
	}

	// Set next waypoint
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);	
	BlackboardComp->SetValueAsObject(NextWaypointKey.SelectedKeyName, Waypoints[Index]);

	// Cycle index
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, (Index + 1) % Waypoints.Num());

	return EBTNodeResult::Succeeded;
}
