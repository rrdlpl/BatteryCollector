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

    /**Returns power to win needed by the HUD*/
    UFUNCTION(BlueprintPure, Category = "Power")
        float GetPowerToWin() const;

protected:
    /** The rate at which the character loses power */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
        float DecayRate;

    ABatteryCollectorCharacter* MyCharacter;

    /**The power needed to win the game*/
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
        float PowerToWin;
    /**The widget class used for the hud screen */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
        TSubclassOf<class UUserWidget> HUDWidgetClass;

    /**The instance */
    UPROPERTY()
        class UUserWidget * CurrentWidget;
};



