// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank() 
{
	/*SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArm);*/
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::MoveTurn);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::FireProjectile);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	TankPlayerController = Cast<APlayerController>(GetController());

	
}

void ATank::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	if (TankPlayerController)
	{
		FHitResult HitResult;

		TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 25, 15, FColor::Red, false, -1);

		RotateTurret(HitResult.ImpactPoint);
	}
}

void ATank::MoveForward(float Value) 
{
	float Time = UGameplayStatics::GetWorldDeltaSeconds(this);

	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = Value * Speed* Time;

	AddActorLocalOffset(DeltaLocation);
}

void ATank::MoveTurn(float Value)  
{
	float Time = UGameplayStatics::GetWorldDeltaSeconds(this);

	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = Value * TurnRotate * Time;

	AddActorLocalRotation(DeltaRotation, true);
}

void ATank::HandleDestruction() 
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}
