// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGM.h"

#include "Kismet/GameplayStatics.h"
#include "TowerTank.h"
#include "PlayerTank.h"

void ABattleBlasterGM::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> TowerTanks;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATowerTank::StaticClass(), TowerTanks);
	TowerCount = TowerTanks.Num();
	if (APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)) {
		Tank = Cast<ABaseTank>(PlayerPawn);
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
}

void ABattleBlasterGM::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank) {
		Cast<APlayerTank>(Tank)->HandleDestruction();
	}
	else {
		if (ATowerTank* tower = Cast<ATowerTank>(DeadActor)) {
			tower->HandleDestruction();
			
			if (--TowerCount == 0) {
				//Victory
			}
		}
	}
}
