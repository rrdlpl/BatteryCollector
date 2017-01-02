// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "BatteryCollector.h"
#include "BatteryCollectorGameMode.h"
#include "BatteryCollectorCharacter.h"
#include "Kismet/GameplayStatics.h"

ABatteryCollectorGameMode::ABatteryCollectorGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	//default decay rate
	DecayRate = 0.01f;
	PrimaryActorTick.bCanEverTick = true;
	
}

void ABatteryCollectorGameMode::BeginPlay()
{
	//Returns Main character
	APawn* CharacterPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	//If we are using battery collector character this cast should be successful.
	MyCharacter = Cast<ABatteryCollectorCharacter>(CharacterPawn);
}

void ABatteryCollectorGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UE_LOG(LogClass, Log, TEXT("Executing tick in game mode "));

	if (MyCharacter)
	{
		if (MyCharacter->GetCurrentsPower() > 0.0f) 
		{
			UE_LOG(LogClass, Log, TEXT("Killing the character "));
			MyCharacter->UpdateCurrentPower(-DeltaSeconds*DecayRate*(MyCharacter->GetInitialPower()));
		}
	}
	else
	{
		UE_LOG(LogClass, Log, TEXT("Character couldnt be cast "));
	}
}
