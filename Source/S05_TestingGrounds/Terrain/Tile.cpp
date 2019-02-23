// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"

#include "ActorPool.h"
#include "NavigationSystem.h"
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
	RandomlyPlaceActors(ToSpawn, Radius, MinSpawn, MaxSpawn, MinScale, MaxScale);
}

void ATile::PlaceAIPawns(TSubclassOf<APawn> ToSpawn, float Radius, int MinSpawn, int MaxSpawn)
{
	RandomlyPlaceActors(ToSpawn, Radius, MinSpawn, MaxSpawn);
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

template<class T>
void ATile::RandomlyPlaceActors(TSubclassOf<T> ToSpawn, float Radius, int MinSpawn, int MaxSpawn, float MinScale, float MaxScale) {
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);

	for (int32 i = 0; i < NumberToSpawn; i++) {
		FVector SpawnPoint;
		if (FindEmptyLocation(SpawnPoint, Radius)) {
			FTransform Transform = FTransform();
			Transform.SetLocation(SpawnPoint);
			Transform.SetScale3D(FVector(FMath::FRandRange(MinScale, MaxScale)));
			PlaceActor(ToSpawn, Transform);
		}
	}
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FTransform Transform)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	if (Spawned) {
		Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
		Spawned->SetActorRelativeLocation(Transform.GetLocation());
		Spawned->SetActorRelativeRotation(FRotator(0, FMath::RandRange(-180, 180), 0));
		Spawned->SetActorScale3D(Transform.GetScale3D());
	}
}

void ATile::PlaceActor(TSubclassOf<APawn> ToSpawn, FTransform Transform)
{
	FRotator Rotation = FRotator(0, FMath::RandRange(-180, 180), 0);
	FVector Location = ActorToWorld().TransformPosition(Transform.GetLocation());
	APawn* Spawned = GetWorld()->SpawnActor<APawn>(ToSpawn, Location, Rotation);
	if (Spawned) {
		Spawned->Tags.Add(FName("Enemy"));
		Spawned->SpawnDefaultController();
	}
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
	UNavigationSystemV1::GetNavigationSystem(GetWorld())->Build();
}
