// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolRoute.generated.h"

/**
* A "route card" to help AI to choose next waypoint
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class S05_TESTINGGROUNDS_API UPatrolRoute : public UActorComponent
{
	GENERATED_BODY()

/** Properties */
private:
	UPROPERTY(EditInstanceOnly, Category = "Patrol")
	TArray<class AActor*> Waypoints;

/** Methods */
public:	
	// Sets default values for this component's properties
	UPatrolRoute();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure, Category = "Patrol")
	TArray<class AActor*> GetWaypoints() { return Waypoints; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;		
	
};
