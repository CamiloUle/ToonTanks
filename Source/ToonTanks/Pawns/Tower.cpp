// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/Tower.h"
#include "Pawns/Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ATower::ATower() 
{
	
}

void ATower::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	RotateEnemyTurret();
}

void ATower::BeginPlay() 
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::RotateEnemyTurret()
{
	if (IsInFireRange()) 
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATower::CheckFireCondition() 
{
	if (IsInFireRange()) 
	{
		FireProjectile();
	}
}

bool ATower::IsInFireRange() 
{
	if (Tank)
	{
		FVector TankLocation = Tank->GetActorLocation();
		FVector TurretLocation = GetActorLocation();

		FVector DirVector = (TankLocation - TurretLocation).GetSafeNormal2D();

		const float DistanceSqr = (TankLocation - TurretLocation).SizeSquared2D();

		if (DistanceSqr <= (Range * Range))
		{
			return true;
		}
	}

	return false;
}

void ATower::HandleDestruction() 
{
	Super::HandleDestruction();
	Destroy();
}