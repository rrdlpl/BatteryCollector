// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryCollector.h"
#include "Pickup.h"


// Sets default values
APickup::APickup()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
    //Create mesh component
    PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
    RootComponent = PickupMesh;

    //All pickup starts active.
    bIsActive = true;
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}


bool APickup::IsActive()
{
    return bIsActive;
}

void APickup::SetActive(bool PickupState)
{
    bIsActive = PickupState;
}

void APickup::OnCollect_Implementation()
{
    FString debugString = GetName();
    UE_LOG(LogClass, Log, TEXT("You have collected %s"), *debugString);

    SetActive(false);
}