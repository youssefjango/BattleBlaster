// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseTank.h"

#include "BattleBlasterGM.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API ABattleBlasterGM : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category = "Game Over")
	float GameOverDelay = 5.0f;
	
	ABaseTank* Tank;
	int32 TowerCount;


	UFUNCTION()
	void ActorDied(AActor* DeadActor);

	void onGameOverTimerTimeOut();

};
