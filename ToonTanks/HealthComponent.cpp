// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameMode.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);

	ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damager, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser)
{
	Health -= Damager;

	if (Health <= 0)
	{
		if (ToonTanksGameMode)
		{
			ToonTanksGameMode->ActorDied(DamagedActor);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Health Component has no reference to the GameMode"));
		}
		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Health left: %f"), Health);
	}
}