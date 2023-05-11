// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/BasePawn.h"
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

	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 200;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRotate = 45;

	APlayerController* GetTankPlayerController() const {return TankPlayerController;}

protected:
	
	virtual void BeginPlay() override;


private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* CameraComp;

	void MoveForward(float Value);
	void MoveTurn(float Value);

	APlayerController* TankPlayerController;
};
