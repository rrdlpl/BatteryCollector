// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "BatteryCollector.h"
#include "BatteryCollectorGameMode.h"
#include "BatteryCollectorCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "SpawnVolume.h"

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
    Super::BeginPlay();
    //find all spawn volume actors.
    InitializeSpawn();
    SetCurrentState(EBatteryPlayState::EPlaying);
    //Returns Main character
    APawn* CharacterPawn = UGameplayStatics::GetPlayerPawn(this, 0);
    //If we are using battery collector character this cast should be successful.
    MyCharacter = Cast<ABatteryCollectorCharacter>(CharacterPawn);
    //Set the score to beat
    if (MyCharacter)
    {
        PowerToWin = MyCharacter->GetInitialPower() * 1.25;
    }
    if (HUDWidgetClass != nullptr)
    {
        CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
        if (CurrentWidget != nullptr)
        {
            CurrentWidget->AddToViewport();
        }
    }
}

float ABatteryCollectorGameMode::GetPowerToWin() const
{
    return PowerToWin;
}

void ABatteryCollectorGameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    UE_LOG(LogClass, Log, TEXT("Executing tick in game mode "));

    if (MyCharacter)
    {
        if (MyCharacter->GetCurrentsPower() > GetPowerToWin())
        {
            SetCurrentState(EBatteryPlayState::EWon);
        }
        else if (MyCharacter->GetCurrentsPower() > 0.0f)
        {
            UE_LOG(LogClass, Log, TEXT("Killing the character "));
            MyCharacter->UpdateCurrentPower(-DeltaSeconds*DecayRate*(MyCharacter->GetInitialPower()));
        }
        else {
            SetCurrentState(EBatteryPlayState::EGameOver);
        }
    }
    else
    {
        UE_LOG(LogClass, Log, TEXT("Character couldnt be cast "));
    }
}

EBatteryPlayState ABatteryCollectorGameMode::GetCurrentState() const
{
    return CurrentState;
}

void ABatteryCollectorGameMode::SetCurrentState(EBatteryPlayState NewState)
{
    CurrentState = NewState;
    HandleNewState(CurrentState);
}

void ABatteryCollectorGameMode::HandleNewState(EBatteryPlayState NewState)
{
    switch (NewState)
    {
        case EBatteryPlayState::EPlaying:
        {
            //spawn volume actives
            ActivateSpawn();
        }
        break;
        case EBatteryPlayState::EWon:
        {
            //spawn volume inactives
            DeactivateSpawn();
        }
        break;
        case EBatteryPlayState::EGameOver:
        {
            //spawn volume inactives
            DeactivateSpawn();
            //block player input
            BlockPlayerInput();
            //ragdoll the character
            RagdollCharacter();
        }break;
        default:
        {

        }
        break;
    }
}

void ABatteryCollectorGameMode::InitializeSpawn()
{
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundActors);

    for (auto Actor : FoundActors)
    {
        ASpawnVolume* SpawnVolumeActor = Cast<ASpawnVolume>(Actor);
        if (SpawnVolumeActor)
        {
            SpawnVolumeActors.AddUnique(SpawnVolumeActor);
        }
    }
}

void ABatteryCollectorGameMode::DeactivateSpawn()
{
    for (ASpawnVolume* Volume : SpawnVolumeActors)
    {
        Volume->SetSpawningActive(false);
    }
}

void ABatteryCollectorGameMode::ActivateSpawn()
{
    for (ASpawnVolume* Volume : SpawnVolumeActors)
    {
        Volume->SetSpawningActive(true);
    }
}

void ABatteryCollectorGameMode::BlockPlayerInput()
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    if (PlayerController) 
    {
        PlayerController->SetCinematicMode(true, false, false, true, true);
    }
}

void ABatteryCollectorGameMode::RagdollCharacter()
{
    ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
    if (MyCharacter)
    {
        MyCharacter->GetMesh()->SetSimulatePhysics(true);
        MyCharacter->GetMovementComponent()->MovementState.bCanJump = false;
    }
}