// Fill out your copyright notice in the Description page of Project Settings.


#include "General/ToonTanksGameMode.h"
#include "Pawns/Tank.h"
#include "Pawns/Tower.h"
#include "General/ToonTanksPlayerController.h"
#include "Kismet/GameplayStatics.h"

AToonTanksGameMode::AToonTanksGameMode() 
{

}


void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AToonTanksGameMode::ActorDie(AActor* DeadActor) 
{
	if (DeadActor == Tank) 
	{
		Tank->HandleDestruction();
		if (PlayerController)
		{
			PlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}

	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor)) 
	{
		DestroyedTower->HandleDestruction();
		TargetTowers--;

		if (TargetTowers == 0) 
		{
			GameOver(true);
		}
	}
}

void AToonTanksGameMode::HandleGameStart() 
{
	TargetTowers = GetTargetTowerCount();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (PlayerController) 
	{
		PlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;

		FTimerDelegate TimerDel = FTimerDelegate::CreateUObject(PlayerController, 
			&AToonTanksPlayerController::SetPlayerEnabledState, 
			true);

		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, TimerDel, StartDelay, false);
	}
}

int32 AToonTanksGameMode::GetTargetTowerCount() 
{
	TArray<AActor*> FindTowers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATower::StaticClass(), FindTowers);
	
	return FindTowers.Num();
}
