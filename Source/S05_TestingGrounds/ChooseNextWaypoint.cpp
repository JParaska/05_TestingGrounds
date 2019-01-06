// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "TP_ThirdPerson/PatrollingGuard.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();

	// Get waypoints	
	auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return EBTNodeResult::Failed;

	auto ControlledPawn = Controller->GetPawn();
	if (!ControlledPawn) return EBTNodeResult::Failed;

	auto Patrol = Cast<APatrollingGuard>(ControlledPawn);
	if (!Patrol) return EBTNodeResult::Failed;

	auto Waypoints = Patrol->GetWaypoints();
	if (Waypoints.Num() == 0) return EBTNodeResult::Failed;

	// Set next waypoint
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);	
	BlackboardComp->SetValueAsObject(NextWaypointKey.SelectedKeyName, Waypoints[Index]);

	// Cycle index
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, (Index + 1) % Waypoints.Num());

	return EBTNodeResult::Succeeded;
}
