// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "S05_TestingGroundsGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class S05_TESTINGGROUNDS_API AInfiniteTerrainGameMode : public AS05_TestingGroundsGameMode
{
	GENERATED_BODY()

/** Properties */
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Navigation")
	class UActorPool* NavVolumePool;

/** Methods */
public:

	AInfiniteTerrainGameMode();

	UFUNCTION(BlueprintPure, Category = "Navigation")
	UActorPool*	GetNavVolumePool() { return NavVolumePool; }
protected:

	UFUNCTION(BlueprintCallable, Category = "Navigation")
	void FindBoundsVolume();
	
};
