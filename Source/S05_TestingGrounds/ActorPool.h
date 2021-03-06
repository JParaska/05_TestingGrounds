// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorPool.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class S05_TESTINGGROUNDS_API UActorPool : public UActorComponent
{
	GENERATED_BODY()

/** Properties */
private:
	TArray<AActor*> Pool;

/** Methods */
public:	
	// Sets default values for this component's properties
	UActorPool();

	/**
	* Allows calling object to get hold of the actor
	*/
	AActor* Checkout();

	/**
	* Returns actor to pool
	*/
	void Return(AActor* ActorToReturn);
};
