// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Pawns/BasePawn.h"
#include "GameFrameWork/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	//RootComponent = CapsuleComp;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = ProjectileMesh;
	//ProjectileMesh->SetupAttachment(CapsuleComp);

	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail Paryticle System"));
	TrailParticles->SetupAttachment(ProjectileMesh);

	ProjectileSound = CreateDefaultSubobject<UAudioComponent>(TEXT("Projectile Sound"));
	ProjectileSound->SetupAttachment(ProjectileMesh);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->MaxSpeed = 1300.f;
	ProjectileMovementComponent->InitialSpeed = 1300.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//SetActorLocation(GetActorLocation() + MovementDirection * Speed * DeltaTime);
	//SetActorRotation(MovementDirection.Rotation());
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalInputs, const FHitResult& Result) 
{
	auto MyOwner = GetOwner();

	if (MyOwner == nullptr) 
	{
		Destroy();
		return;
	}
		
	auto MyOwnerinstigator = MyOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner) 
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerinstigator, this, DamageTypeClass);
		if (HitParticles) 
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, GetActorLocation(), GetActorRotation());
		}
	}
	Destroy();	
}

