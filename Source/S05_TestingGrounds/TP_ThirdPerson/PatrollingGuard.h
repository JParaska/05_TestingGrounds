// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "PatrollingGuard.generated.h"

/**
 * 
 */
UCLASS()
class S05_TESTINGGROUNDS_API APatrollingGuard : public ATP_ThirdPersonCharacter
{
	GENERATED_BODY()
	
/** Properties */
private:
	UPROPERTY(EditInstanceOnly, Category = "Patrol")
	TArray<class AActor*> Waypoints;

/** Methods */
public:
	UFUNCTION(BlueprintPure, Category = "Patrol")
	TArray<class AActor*> GetWaypoints() { return Waypoints; }
	
};
