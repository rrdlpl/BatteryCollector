// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "Pickup.h"
#include "BatteryPickup.generated.h"

/**
*
*/
UCLASS()
class BATTERYCOLLECTOR_API ABatteryPickup : public APickup
{
	GENERATED_BODY()
public:
	//Constructor
	ABatteryPickup();
	/**Use OnCollect Implementation because it is a blueprint native event*/

	void OnCollect_Implementation() override;

	UFUNCTION(BlueprintPure, Category = "Power")
	float GetBatteryPower();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power")
	float BatteryPower;
};
