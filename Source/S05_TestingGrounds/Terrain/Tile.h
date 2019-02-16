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

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MinExtent;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MaxExtent;

	UPROPERTY(EditDefaultsOnly, Category = "Navigation")
	FVector NavigationBoundsOFfset;

/** Methods */	
public:	
	// Sets default values for this actor's properties
	ATile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Terrain")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, float Radius = 100, int MinSpawn = 1, int MaxSpawn = 1, float MinScale = 1, float MaxScale = 1);

	UFUNCTION(BlueprintCallable, Category = "Terrain")
	void PlaceAIPawns(TSubclassOf<APawn> ToSpawn, float Radius = 100, int MinSpawn = 1, int MaxSpawn = 1);

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetPool(UActorPool* InPool);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

private:

	bool FindEmptyLocation(FVector& EmptyLocation, float Radius);

	template<class T>
	void RandomlyPlaceActors(TSubclassOf<T> ToSpawn, float Radius = 100, int MinSpawn = 1, int MaxSpawn = 1, float MinScale = 1, float MaxScale = 1);
	
	void PlaceActor(TSubclassOf<AActor> ToSpawn, FTransform Transform);

	void PlaceActor(TSubclassOf<APawn> ToSpawn, FTransform Transform);

	bool CanSpawnAtLocation(FVector Location, float Radius);

	void PositionNavMeshBoundsVolume();

};
