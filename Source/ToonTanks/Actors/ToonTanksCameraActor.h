// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "ToonTanksCameraActor.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksCameraActor : public ACameraActor
{
	GENERATED_BODY()

public:
	AToonTanksCameraActor();

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	virtual void FollowCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ATank* Tank;

	float CameraDistance = 400.f;

protected:
	
	

private:

};
