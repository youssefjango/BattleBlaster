// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTank.h"

APlayerTank::APlayerTank()
{
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	
	SpringArm->SetupAttachment(RootComponent);
	CameraComp->SetupAttachment(SpringArm);
}

void APlayerTank::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController) {
		ULocalPlayer* localPlayer = PlayerController->GetLocalPlayer();
		if(localPlayer){
			UEnhancedInputLocalPlayerSubsystem* Subsystem;
			Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(localPlayer);
			if (Subsystem) {
				Subsystem->AddMappingContext(DefaultMappingInput, 0);
			}
		}
	}
}

// Called every frame
void APlayerTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

