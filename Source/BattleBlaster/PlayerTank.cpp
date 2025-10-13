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
	LL = CreateDefaultSubobject<USpotLightComponent>(TEXT("LeftLightSpot"));
	LL->SetupAttachment(TurretMesh);
	LR = CreateDefaultSubobject<USpotLightComponent>(TEXT("RightLightSpot"));
	LR->SetupAttachment(TurretMesh);
	SpringArm->SetupAttachment(RootComponent);
	CameraComp->SetupAttachment(SpringArm);
	TrailParticles = CreateDefaultSubobject<UNiagaraComponent>(TEXT("TrailTank"));
	TrailParticles->SetupAttachment(RootComponent);
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
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &APlayerTank::MoveInput);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &APlayerTank::TurnInput);
		EnhancedInputComponent->BindAction(LightAction, ETriggerEvent::Started, this, &APlayerTank::LightInput);
		EnhancedInputComponent->BindAction(LightIntensityAction, ETriggerEvent::Triggered, this, &APlayerTank::IntensityLightInput);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ABaseTank::Fire);
	}
}

void APlayerTank::IntensityLightInput(const FInputActionValue& Value)
{
	float InValue = Value.Get<float>();
	if (IsInvalidRequest(InValue)) {
		return;
	}
	LR->SetIntensity(LR->Intensity + InValue * 20);
	LL->SetIntensity(LL->Intensity + InValue * 20);
	

	
}


void APlayerTank::LightInput(const FInputActionValue& Value)
{
	bool InValue = Value.Get<bool>();

	LR->ToggleVisibility();
	LL->ToggleVisibility();
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), LightBlinkSound, GetActorLocation());
}
void APlayerTank::MoveInput(const FInputActionValue& Value)
{
	float InValue = Value.Get<float>();
	if (InValue == 0) { //when button is realised
		TrailParticles->Deactivate();
		return;
	}


	FVector DeltaLoc = FVector(Speed * InValue * UGameplayStatics::GetWorldDeltaSeconds(this)
		, 0.0f, 0.0f);

	AddActorLocalOffset(DeltaLoc, true);
	TrailParticles->Activate();
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

bool APlayerTank::IsInvalidRequest(float InValue)
{
	return (InValue > 0 && (LR->Intensity > 500.0f || LL->Intensity > 500.0f)) || (InValue < 0 && (LR->Intensity <= 0.0f || LL->Intensity <= 0.0f));
}

