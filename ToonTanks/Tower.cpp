// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Tank.h"
#include "Tower.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();

	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerTank) return;

	DistanceToPlayer = FVector::Dist(GetActorLocation(), PlayerTank->GetActorLocation());

	if(DistanceToPlayer < FireRange)
	{
		RotateTurret(PlayerTank->GetActorLocation());
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::CheckFireCondition()
{
	if (!PlayerTank) return;

	if (DistanceToPlayer < FireRange && PlayerTank->bAlive)
	{
		Fire();
	}
}