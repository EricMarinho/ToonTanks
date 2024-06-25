// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksPlayerController.h"
#include "Tank.h"
#include "Tower.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == PlayerTank)
	{
		PlayerTank->HandleDestruction();
		if (!PlayerController) return;
		PlayerController->SetPlayerEnabledState(false);
		GameOver(false);
		// Restart the game after 3 seconds
		FTimerHandle RestartTimerHandle;
		GetWorldTimerManager().SetTimer(RestartTimerHandle, this, &AToonTanksGameMode::RestartGame, RestartDelay);
	}
	else if(ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();

		if (--TargetTowers == 0)
		{
			if (!PlayerController) return;
			PlayerController->SetPlayerEnabledState(false);
			GameOver(true);
			// Restart the game after 3 seconds
			FTimerHandle RestartTimerHandle;
			GetWorldTimerManager().SetTimer(RestartTimerHandle, this, &AToonTanksGameMode::RestartGame, RestartDelay);
		}
	}

	
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	TargetTowers = GetTargetTowersCount();

	HandleGameStart();

	StartGame();
}

void AToonTanksGameMode::HandleGameStart()
{
	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	
	if (!PlayerController) return;
	PlayerController->SetPlayerEnabledState(false);

	FTimerHandle PlayerEnableTimerHandle;

	FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);
	GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableDelegate, StartDelay, false);
}

int32 AToonTanksGameMode::GetTargetTowersCount()
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
	return Towers.Num();
}

void AToonTanksGameMode::RestartGame()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}
