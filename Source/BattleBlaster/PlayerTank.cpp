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


	if (APlayerController* PlayerController
		= Cast<APlayerController>(Controller)) {
		ULocalPlayer* localPlayer = PlayerController->GetLocalPlayer();
		if (localPlayer) {

			if (UEnhancedInputLocalPlayerSubsystem* Subsystem
				= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(localPlayer)) {
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

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerTank::MoveInput);
	}
}

void APlayerTank::MoveInput(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("Value: %f"), Value.Get<float>());
	float InValue = Value.Get<float>();

	FVector DeltaLoc = FVector(Speed * InValue * UGameplayStatics::GetWorldDeltaSeconds(this)
		, 0.0f, 0.0f);

	AddActorLocalOffset(DeltaLoc);
}

