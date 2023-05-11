// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

		

public:

	ATower();

	virtual void Tick(float DeltaTime) override;
	virtual void RotateEnemyTurret();
	
	void CheckFireCondition();
	void HandleDestruction();

	bool IsInFireRange();

	UPROPERTY()
	class ATank* Tank;

	FTimerHandle FireRateTimerHandle;

	float FireRate = 2.f;
	const float Range = 800;

protected:

	virtual void BeginPlay() override;

private:
	

};
