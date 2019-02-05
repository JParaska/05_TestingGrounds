// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class S05_TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()

/** Properties */
private:
	UPROPERTY()
	class UActorPool* Pool;

	AActor* NavMeshBoundsVolume;

/** Methods */	
public:	
	// Sets default values for this actor's properties
	ATile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Terrain")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, float Radius = 100, int MinSpawn = 1, int MaxSpawn = 1, float MinScale = 1, float MaxScale = 1);

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetPool(UActorPool* InPool);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

private:

	bool FindEmptyLocation(FVector& EmptyLocation, float Radius);
	
	void PlaceActor(TSubclassOf<AActor> ToSpawn, FVector Location, float Scale);

	bool CanSpawnAtLocation(FVector Location, float Radius);

	void PositionNavMeshBoundsVolume();

};
