// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryCollector.h"
#include "BatteryPickup.h"



ABatteryPickup::ABatteryPickup()
{
	GetMesh()->SetSimulatePhysics(true);
	BatteryPower = 200.0f;
}


void ABatteryPickup::OnCollect_Implementation()
{
	//Use the base implementation.
	Super::OnCollect_Implementation();


	//Destroy the battery
	Destroy();
}

float ABatteryPickup::GetBatteryPower()
{
	return BatteryPower;
}