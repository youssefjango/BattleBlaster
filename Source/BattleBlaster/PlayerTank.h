// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTank.h"

#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"



#include "PlayerTank.generated.h"

/**
 *
 */
UCLASS()
class BATTLEBLASTER_API APlayerTank : public ABaseTank
{
	GENERATED_BODY()

public:
	APlayerTank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* DefaultMappingInput;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* TurnAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* FireAction;
	
	UPROPERTY(EditAnywhere, Category = "Motion")
	float Speed = 300.0f;
	UPROPERTY(EditAnywhere, Category = "Motion")
	float RotationRate = 50.0f;
	

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComp;

	APlayerController* PlayerController;

	void MoveInput(const FInputActionValue& Value);
	void TurnInput(const FInputActionValue& Value);
	void HandleDestruction();
	void SetPlayerEnabled(bool Enabled);
};
