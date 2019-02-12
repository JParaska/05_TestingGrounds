// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"

#include "ActorPool.h"
#include "AI/Navigation/NavigationSystem.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MinExtent = FVector(0, -2000, 0);
	MaxExtent = FVector(4000, 2000, 0);

	NavigationBoundsOFfset = FVector(2000, 0, 0);
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Pool->Return(NavMeshBoundsVolume);
	Super::EndPlay(EndPlayReason);
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

void ATile::PlaceAIPawns(TSubclassOf<APawn> ToSpawn, float Radius, int MinSpawn, int MaxSpawn)
{
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);

	for (int32 i = 0; i < NumberToSpawn; i++) {
		FVector SpawnPoint;
		if (FindEmptyLocation(SpawnPoint, Radius)) {
			PlaceAIPawn(ToSpawn, SpawnPoint);
		}
	}
}

void ATile::SetPool(UActorPool * InPool)
{
	Pool = InPool;

	PositionNavMeshBoundsVolume();
}

bool ATile::FindEmptyLocation(FVector& EmptyLocation, float Radius)
{
	FBox Bounds(MinExtent, MaxExtent);

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

void ATile::PlaceAIPawn(TSubclassOf<APawn> ToSpawn, FVector SpawnPoint)
{
	APawn* Spawned = GetWorld()->SpawnActor<APawn>(ToSpawn);
	Spawned->SetActorLocation(ActorToWorld().TransformPosition(SpawnPoint));
	Spawned->SetActorRotation(FRotator(0, FMath::RandRange(-180, 180), 0));

	Spawned->Tags.Add(FName("Enemy"));
	Spawned->SpawnDefaultController();
}

bool ATile::CanSpawnAtLocation(FVector Location, float Radius)
{
	// TODO fix barrier!!
	FHitResult Hit;
	FVector WorldLocation = ActorToWorld().TransformPosition(Location);
	return !GetWorld()->SweepSingleByChannel(Hit, WorldLocation, WorldLocation, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius));
}

void ATile::PositionNavMeshBoundsVolume()
{
	NavMeshBoundsVolume = Pool->Checkout();
	if (NavMeshBoundsVolume == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Empty pool"));
		return;
	}
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation() + NavigationBoundsOFfset);
	GetWorld()->GetNavigationSystem()->Build();
}
