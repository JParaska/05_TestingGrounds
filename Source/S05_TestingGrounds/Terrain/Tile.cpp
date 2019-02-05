// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"

#include "ActorPool.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, float Radius, int MinSpawn, int MaxSpawn, float MinScale, float MaxScale)
{
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);

	for (int32 i = 0; i < NumberToSpawn; i++) {
		FVector SpawnPoint;
		float RandomScale = FMath::RandRange(MinScale, MaxScale);
		if (FindEmptyLocation(SpawnPoint, Radius * RandomScale)) {
			PlaceActor(ToSpawn, SpawnPoint, RandomScale);
		}
	}
}

void ATile::SetPool(UActorPool * InPool)
{
	Pool = InPool;
}

bool ATile::FindEmptyLocation(FVector& EmptyLocation, float Radius)
{
	FVector Min(0, -2000, 0);
	FVector Max(4000, 2000, 0);
	FBox Bounds(Min, Max);

	const int MAX_ATTEMPTS = 100;
	for (int32 i = 0; i < MAX_ATTEMPTS; i++)
	{
		FVector EmptySpaceCandidate = FMath::RandPointInBox(Bounds);
		if (CanSpawnAtLocation(EmptySpaceCandidate, Radius)) {			
			EmptyLocation = EmptySpaceCandidate;
			return true;
		}
	}
	return false;
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector Location, float Scale)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
	Spawned->SetActorRelativeLocation(Location);
	Spawned->SetActorRelativeRotation(FRotator(0, FMath::RandRange(-180, 180), 0));
	Spawned->SetActorScale3D(FVector(Scale));
}

bool ATile::CanSpawnAtLocation(FVector Location, float Radius)
{
	// TODO fix barrier!!
	FHitResult Hit;
	FVector WorldLocation = ActorToWorld().TransformPosition(Location);
	return !GetWorld()->SweepSingleByChannel(Hit, WorldLocation, WorldLocation, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius));
}
