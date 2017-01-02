// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameModeBase.h"
#include "BatteryCollectorCharacter.h"
#include "BatteryCollectorGameMode.generated.h"

UCLASS(minimalapi)
class ABatteryCollectorGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ABatteryCollectorGameMode();

    virtual void Tick(float DeltaSeconds) override;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
protected:
    /** The rate at which the character loses power */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power")
        float DecayRate;

    ABatteryCollectorCharacter* MyCharacter;
};



