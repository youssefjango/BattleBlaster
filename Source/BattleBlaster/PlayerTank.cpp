// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "InputMappingContext.h"
#include "Kismet/GameplayStatics.h"

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
	PlayerController = Cast<APlayerController>(Controller);

	if (PlayerController) {
		ULocalPlayer* localPlayer = PlayerController->GetLocalPlayer();
		if (localPlayer) {

			if (UEnhancedInputLocalPlayerSubsystem* Subsystem
				= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(localPlayer)) {
				Subsystem->AddMappingContext(DefaultMappingInput, 0);
			}
		}
	}
	SetPlayerEnabled(false);
}

// Called every frame
void APlayerTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerController){
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

		Super::RotateTurret(HitResult.ImpactPoint);
	}
}

// Called to bind functionality to input
void APlayerTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerTank::MoveInput);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &APlayerTank::TurnInput);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ABaseTank::Fire);
	}
}

void APlayerTank::MoveInput(const FInputActionValue& Value)
{
	float InValue = Value.Get<float>();

	FVector DeltaLoc = FVector(Speed * InValue * UGameplayStatics::GetWorldDeltaSeconds(this)
		, 0.0f, 0.0f);

	AddActorLocalOffset(DeltaLoc);
}
void APlayerTank::TurnInput(const FInputActionValue& Value)
{
	float InValue = Value.Get<float>();

	FRotator DeltaRotation = FRotator(0.0f, 
		RotationRate * InValue * UGameplayStatics::GetWorldDeltaSeconds(this), 0.0f);

	AddActorLocalRotation(DeltaRotation, true);
}

void APlayerTank::HandleDestruction() {
	
	Super::HandleDestruction();

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	SetPlayerEnabled(false);
	IsAlive = false;
	
}

void APlayerTank::SetPlayerEnabled(bool Enabled)
{
	if (PlayerController) {
	
		if (Enabled) {
			EnableInput(PlayerController);
		}
		else {
			DisableInput(PlayerController);
		}
		PlayerController->bShowMouseCursor = Enabled;


	}
}

