// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ToonTanksCameraActor.h"
#include "Pawns/Tank.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

AToonTanksCameraActor::AToonTanksCameraActor() 
{
	PrimaryActorTick.bCanEverTick = true;
}

void AToonTanksCameraActor::BeginPlay() 
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

}

void AToonTanksCameraActor::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	FollowCharacter();
}

void AToonTanksCameraActor::FollowCharacter() 
{
	FVector TankLocation;
	FVector CameraLocation = GetActorLocation();
	if (Tank) 
	{
		TankLocation = Tank->GetActorLocation();
		
		CameraLocation.X = TankLocation.X - CameraDistance;
		CameraLocation.Y = TankLocation.Y;

		SetActorLocation(CameraLocation);
	}
}