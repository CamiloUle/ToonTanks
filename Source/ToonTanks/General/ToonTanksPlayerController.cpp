// Fill out your copyright notice in the Description page of Project Settings.


#include "General/ToonTanksPlayerController.h"
#include "Pawns/BasePawn.h"

AToonTanksPlayerController::AToonTanksPlayerController() 
{

}

void AToonTanksPlayerController::SetPlayerEnabledState(bool bIsPlayerEnabled) 
{
	if (bIsPlayerEnabled) 
	{
		GetPawn()->EnableInput(this);
	}
	else 
	{
		GetPawn()->DisableInput(this);
	}
	bShowMouseCursor = bIsPlayerEnabled;
}