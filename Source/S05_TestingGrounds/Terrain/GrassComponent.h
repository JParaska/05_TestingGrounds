// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "GrassComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class S05_TESTINGGROUNDS_API UGrassComponent : public UHierarchicalInstancedStaticMeshComponent
{
	GENERATED_BODY()

/** Properties */
public:
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FBox SpawningExtents;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	int SpawnCount;

/** Methods */
public:	
	// Sets default values for this component's properties
	UGrassComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	void SpawnGrass();
	
};
