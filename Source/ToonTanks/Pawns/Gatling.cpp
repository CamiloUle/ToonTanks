// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/Gatling.h"
#include "Pawns/Tank.h"
#include "Pawns/Tower.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

AGatling::AGatling()
{

}

void AGatling::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateEnemyTurret();
}

void AGatling::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	//GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void AGatling::RotateEnemyTurret()
{
	if (IsInFireRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

void AGatling::CheckFireCondition()
{
	if (IsInFireRange())
	{
		FireProjectile();
	}
}

bool AGatling::IsInFireRange()
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

void AGatling::HandleDestruction()
{
	//Super::HandleDestruction();
	Destroy();
}