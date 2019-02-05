// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameMode.h"

#include "ActorPool.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


AInfiniteTerrainGameMode::AInfiniteTerrainGameMode() {
	NavVolumePool = CreateDefaultSubobject<UActorPool>(FName("NavMeshBoundsVolumePool"));
}

void AInfiniteTerrainGameMode::FindBoundsVolume()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANavMeshBoundsVolume::StaticClass(), FoundActors);

	for (AActor* FoundActor : FoundActors) {
		NavVolumePool->Return(FoundActor);
	}
}
