// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerTank.h"

void ATowerTank::BeginPlay()
{
	Super::BeginPlay();
}

void ATowerTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Tank && (FVector::Distance(TurretMesh->GetComponentLocation(), Tank->GetActorLocation()) <= ShootingRange)) {
		RotateTurret(Tank->GetActorLocation());
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("Player Tank not set make sure to set it properly in GameMode"));
	}
}
