// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameMode.h"

#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

void AInfiniteTerrainGameMode::FindBoundsVolume()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANavMeshBoundsVolume::StaticClass(), FoundActors);

	for (AActor* FoundActor : FoundActors) {
		ANavMeshBoundsVolume* NavVolume = Cast<ANavMeshBoundsVolume>(FoundActor);
		if (NavVolume != nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("Found NavMesh: %s"), *NavVolume->GetName());
		}
	}
}