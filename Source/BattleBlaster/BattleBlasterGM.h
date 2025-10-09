// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseTank.h"
#include "PlayerTank.h"
#include "ScreenMessageUI.h"

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
	TSubclassOf<UScreenMessageUI> ScreenMessageUI;
	
	UScreenMessageUI* MessageWidgetUI;
	
	UPROPERTY(EditAnywhere, Category = "Game Over")
	float GameOverDelay = 5.0f;
	
	APlayerTank* Tank;
	int32 TowerCount;
	bool IsVictory = false;

	UPROPERTY(EditAnywhere)
	int32 CountDownDelay = 5;

	int32 CountDownSeconds;

	FTimerHandle CountdownTimerHandle;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShakeBase> DeathShake;



	UFUNCTION()
	void ActorDied(AActor* DeadActor);

	void onGameOverTimerTimeOut();
	void OnCountDownTimerTimeOut();

};
