// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	AToonTanksGameMode();

	void ActorDie(AActor* DeadActor);

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWoonGame);

private:

	class ATank* Tank;
	class AToonTanksPlayerController* PlayerController;

	float StartDelay = 3.f;
	
	int32 TargetTowers = 0;
	int32 GetTargetTowerCount();

	void HandleGameStart();
	
};
