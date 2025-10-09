// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerTank.h"
#include "EnemyTank.generated.h"

/**
 * Class to be implemented after finishing up the main game to create more enemy types using AI to patrol, chase, and explode
 */
UCLASS()
class BATTLEBLASTER_API AEnemyTank : public ATowerTank
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere)
	FString AIState;
};
