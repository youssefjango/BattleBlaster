// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGM.h"

#include "Kismet/GameplayStatics.h"
#include "TowerTank.h"
#include "PlayerTank.h"
#include "BattleBlasterGameInstance.h"

void ABattleBlasterGM::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> TowerTanks;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATowerTank::StaticClass(), TowerTanks);
	TowerCount = TowerTanks.Num();
	if (APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)) {
		Tank = Cast<APlayerTank>(PlayerPawn);
		if (!Tank) {
			UE_LOG(LogTemp, Display, TEXT("GameMode: Failed registering palyer pawn as tank."));
		}
	}
	if (Tank) {
		for (int32 i = 0; TowerCount > i; i++) {
			if (ATowerTank * Tower = Cast<ATowerTank>(TowerTanks[i])) {
				Tower->Tank = this->Tank;
			}
		}
	}

	CountDownSeconds = CountDownDelay;
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ABattleBlasterGM::OnCountDownTimerTimeOut, 1.0f, true);
}

void ABattleBlasterGM::ActorDied(AActor* DeadActor)
{
	bool IsGameOver = false;

	if (DeadActor == Tank) {
		Tank->HandleDestruction();
		IsGameOver = true;
	}
	else {
		if (ATowerTank* tower = Cast<ATowerTank>(DeadActor)) {
			tower->HandleDestruction();
			
			if (--TowerCount == 0) {
				IsGameOver = true;
				IsVictory = true;
			}
		}
	}

	if (IsGameOver) {
		FString GameOverString = IsGameOver ? "Victory!" : "Defeat :(";
		
		FTimerHandle GameOverTimerHandle;
		GetWorldTimerManager().SetTimer(GameOverTimerHandle, this, &ABattleBlasterGM::onGameOverTimerTimeOut, GameOverDelay, false);
	}
}

void ABattleBlasterGM::onGameOverTimerTimeOut()
{	
	if (UBattleBlasterGameInstance * BBGI = Cast<UBattleBlasterGameInstance>(GetGameInstance())) {
		if (IsVictory) {
			UE_LOG(LogTemp, Display, TEXT("VICTORY!"));
		}
		IsVictory ? BBGI->LoadNextLevel() : BBGI->RestartCurrentLevel();
	}
}

void ABattleBlasterGM::OnCountDownTimerTimeOut()
{
	if (CountDownSeconds > 0) {
		UE_LOG(LogTemp, Display, TEXT("CountDown: %d"), CountDownSeconds);
	}
	else if (CountDownSeconds == 0)
	{
		UE_LOG(LogTemp, Display, TEXT("GO!"));
		Tank->SetPlayerEnabled(true);
	}
	else {
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
	}
	CountDownSeconds--;
	
}
