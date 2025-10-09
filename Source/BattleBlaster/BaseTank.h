// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "Projectile.h"


#include "BaseTank.generated.h"



UCLASS()
class BATTLEBLASTER_API ABaseTank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseTank();

	UPROPERTY(EditAnywhere, Category = "Turret Motion")
	float TurretRotationSpeed = 10.0f;

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* ProjectileStartingPoint;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* Explosion;
	UPROPERTY(EditAnywhere)
	USoundBase* ExplosionSound;
	


	bool IsAlive = true;

	void RotateTurret(FVector lookAtTarget);

	void Fire();

	void HandleDestruction();
};
