// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryCollector.h"
#include "Pickup.h"
#include "SpawnVolume.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
    //Create the boxc component to represent the spawn volume
    WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
    RootComponent = WhereToSpawn;

    //Set the spawn delay
    SpawnDelayRangeLow = 1.0f;
    SpawnDelayRangeHigh = 4.5f;
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
    Super::BeginPlay();

    UpdateSpawnTimer();

}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

FVector ASpawnVolume::GetRandomPointInVolume()
{
    FVector SpawnOrigin = WhereToSpawn->Bounds.Origin;
    FVector SpawnExtent = WhereToSpawn->Bounds.BoxExtent;
    return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
}

FRotator ASpawnVolume::GetRandomRotation()
{
    FRotator SpawnRotation;
    SpawnRotation.Yaw = FMath::FRand() * 360.0;
    SpawnRotation.Pitch = FMath::FRand() * 360.0;
    SpawnRotation.Roll = FMath::FRand() * 360.0;
    return SpawnRotation;
}

void ASpawnVolume::SpawnPickup()
{
    if (WhatToSpawn == NULL)
    {
        return;
    }

    UWorld* const World = GetWorld();
    if (World)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = Instigator;
        //Get random position to spawn
        FVector SpawnLocation = GetRandomPointInVolume();

        //Get random rotation
        FRotator SpawnRotation = GetRandomRotation();

        APickup* const SpawnedPickup = World->SpawnActor<APickup>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams);

        UpdateSpawnTimer();

    }
}

void ASpawnVolume::UpdateSpawnTimer()
{
    SpawnDelay = FMath::RandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);

    GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, SpawnDelay, false);
}
