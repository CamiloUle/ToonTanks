// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/BasePawn.h"
#include "Gatling.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AGatling : public ABasePawn
{
	GENERATED_BODY()

public:
	AGatling();

	virtual void Tick(float DeltaTime) override;
	virtual void RotateEnemyTurret();
	
	void CheckFireCondition();
	void HandleDestruction();

	bool IsInFireRange();

	FTimerHandle FireRateTimerHandle;

	float FireRate = 0.2f;
	const float Range = 800;

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY()
	class ATank* Tank;

};
