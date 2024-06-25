// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 *
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void HandleDestruction();

	bool bAlive = true;

	APlayerController* PlayerController;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* TurnAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* FireAction;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 400.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnSpeed = 400.0f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireRate = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireCoolDown = 0.0f;

	void Move(const struct FInputActionValue& Value);

	void Turn(const struct FInputActionValue& Value);
};