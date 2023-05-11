// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/AudioComponent.h"
#include "DrawDebugHelpers.h"
#include "Actors/Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"


// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT( "Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input

void ABasePawn::RotateTurret(FVector LookAtTarget) 
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LooAtRotation = FRotator(0.f,ToTarget.Rotation().Yaw, 0.f);
	
	float Time = UGameplayStatics::GetWorldDeltaSeconds(this);

	FRotator RotatorTouse = FMath::RInterpTo(TurretMesh->GetComponentRotation(), LooAtRotation, Time, 10);

	TurretMesh->SetWorldRotation(RotatorTouse);
}

void ABasePawn::FireProjectile() 
{
	FVector ProjectileLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator ProjectielRotation = ProjectileSpawnPoint->GetComponentRotation();

	FVector DirProjectile = TurretMesh->GetComponentLocation().GetSafeNormal2D();

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileLocation, ProjectielRotation);
	
	Projectile->SetOwner(this);
}

void ABasePawn::HandleDestruction() 
{
	UGameplayStatics::CreateSound2D(GetWorld(), DestroyPawnSound);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyPawnParticleSystem, GetActorLocation(), GetActorRotation());
}
