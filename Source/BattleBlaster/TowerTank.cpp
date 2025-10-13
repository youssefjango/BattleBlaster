// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerTank.h"
#include "PlayerTank.h"
ATowerTank::ATowerTank() {
	LightTurret = CreateDefaultSubobject<USpotLightComponent>(TEXT("LightTurret"));
	LightTurret->SetupAttachment(TurretMesh);
}
void ATowerTank::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle FireTimerHandle;
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ATowerTank::CheckFireCondition, FireRate, true);
}

void ATowerTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Tank && InFireRange() && Tank->IsAlive) {
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATowerTank::CheckFireCondition()
{
	if (Tank && Tank->IsAlive && InFireRange())
	{
		Fire();
	}
}
bool ATowerTank::InFireRange(){
	return (FVector::Distance(TurretMesh->GetComponentLocation(), Tank->GetActorLocation()) <= ShootingRange);
}

void ATowerTank::HandleDestruction() {
	Super::HandleDestruction();
	Destroy();
}
