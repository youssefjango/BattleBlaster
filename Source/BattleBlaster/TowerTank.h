// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTank.h"
#include "TowerTank.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API ATowerTank : public ABaseTank
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

	ABaseTank* Tank;

	UPROPERTY(EditAnywhere, Category = "Shooting")
	float ShootingRange = 500.0f;
	
};
