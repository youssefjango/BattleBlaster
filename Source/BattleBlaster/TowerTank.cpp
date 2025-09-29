// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerTank.h"

void ATowerTank::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle FireTimerHandle;
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ATowerTank::CheckFireCondition, FireRate, true);
}

void ATowerTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Tank && InFireRange()) {
		RotateTurret(Tank->GetActorLocation());
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("Player Tank not set make sure to set it properly in GameMode"));
	}
}

void ATowerTank::CheckFireCondition()
{
	if (Tank && InFireRange())
	{
		Fire();

	}
}
bool ATowerTank::InFireRange(){
	return (FVector::Distance(TurretMesh->GetComponentLocation(), Tank->GetActorLocation()) <= ShootingRange);
}
