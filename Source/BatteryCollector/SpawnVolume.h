// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class BATTERYCOLLECTOR_API ASpawnVolume : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ASpawnVolume();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaSeconds) override;

    FORCEINLINE class UBoxComponent* GetWhereToSpawn() const { return WhereToSpawn; };
    /**Returns random point within box component*/
    UFUNCTION(BlueprintPure, Category = "Spawning")
        FVector GetRandomPointInVolume();

    UFUNCTION(BlueprintPure, Category = "Spawning")
        FRotator GetRandomRotation();

protected:

    /** The pickup to spawn */
    UPROPERTY(EditAnywhere, Category = "Spawning")
        TSubclassOf<class APickup> WhatToSpawn;

    FTimerHandle SpawnTimer;

    /** Minimum spawn delay*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
        float SpawnDelayRangeLow;

    /** Max spawn delay*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
        float SpawnDelayRangeHigh;

private:
    /** Box to specify where the battery should spawn*/
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
    class UBoxComponent* WhereToSpawn;

    void SpawnPickup();
    /**The current spawn delay*/
    float SpawnDelay;

    void UpdateSpawnTimer();
};
