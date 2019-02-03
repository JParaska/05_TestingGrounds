// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"

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

	FVector Location = GetActorLocation();
	FColor C = CastSphere(Location, 250) ? FColor::Red : FColor::Green;
	DrawDebugSphere(GetWorld(), Location, 250, 64,C, true, 1000);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn)
{
	FVector Min(0, -2000, 0);
	FVector Max(4000, 2000, 0);
	FBox Bounds(Min, Max);
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);

	for (int32 i = 0; i < NumberToSpawn; i++) {
		FVector SpawnPoint = FMath::RandPointInBox(Bounds);
		AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
		Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
		Spawned->SetActorRelativeLocation(SpawnPoint);
	}
}

bool ATile::CastSphere(FVector Location, float Radius)
{
	FHitResult Hit;
	return GetWorld()->SweepSingleByChannel(Hit, Location, Location, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius));
}
