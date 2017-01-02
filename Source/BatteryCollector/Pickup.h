// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class BATTERYCOLLECTOR_API APickup : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickup();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	//Returns the mesh for the pickup
	FORCEINLINE class UStaticMeshComponent * GetMesh() const { return PickupMesh; };

	/** Returns whether pickup is active or not */
	UFUNCTION(BlueprintPure, Category = "Pickup")
		bool IsActive();

	/** Allows other classes to change whether the pickup is active or not.*/
	UFUNCTION(BlueprintCallable, Category = "Pickup")
		void SetActive(bool PickupState);


	UFUNCTION(BlueprintNativeEvent)
		void OnCollect();
	virtual void OnCollect_Implementation();

protected:
	/** True when the pickup can be used, false when it is deactivated */
	bool bIsActive;

private:
	/** Static mesh to represent the pickup in the level. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PickupMesh;

};
