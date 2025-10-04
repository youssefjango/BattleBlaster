// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTank.h"

// Sets default values
ABaseTank::ABaseTank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));;
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));;
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileStartingPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileStartingPoint"));;
	ProjectileStartingPoint->SetupAttachment(TurretMesh);
}

void ABaseTank::RotateTurret(FVector lookAtTarget)
{
	FVector VectorToTarget = lookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.0f, VectorToTarget.Rotation().Yaw, 0.0f);
	FRotator InterpolatedRotation = FMath::RInterpTo(TurretMesh->GetComponentRotation()
		,LookAtRotation
		,GetWorld()->GetDeltaSeconds()
		,TurretRotationSpeed
		);
	
	TurretMesh->SetWorldRotation(InterpolatedRotation);
}

void ABaseTank::Fire() {
	FVector SpawnLoc = ProjectileStartingPoint->GetComponentLocation();
	FRotator SpawnRot = ProjectileStartingPoint->GetComponentRotation();
	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLoc, SpawnRot);
	if (projectile) {
		projectile->SetOwner(this);
	}
}

