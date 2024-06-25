// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	virtual void HandleDestruction();

private
:
	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireRange = 500.0f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireRate = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireCoolDown = 0.0f;

	class ATank* PlayerTank;

	FTimerHandle FireRateTimerHandle;

	float DistanceToPlayer = 0.0f;

	void CheckFireCondition();
};
