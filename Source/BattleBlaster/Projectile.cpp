// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Proj = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	SetRootComponent(Proj);
	ProjMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));

	TrailParticles = CreateDefaultSubobject<UNiagaraComponent>(TEXT("TrailParticles"));
	TrailParticles->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	Proj->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if (LaunchSound) {
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), LaunchSound, GetActorLocation());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No sound for launch assigned. aka [LaunchSound] in Projectile"));
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* OwnerOfProjectile = GetOwner();
	if (OwnerOfProjectile && OtherActor && OtherActor != Owner && OtherActor != this) {
		UGameplayStatics::ApplyDamage(OtherActor, Damage, OwnerOfProjectile->GetInstigatorController(), this, UDamageType::StaticClass());

		if (HitParticles) {
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitParticles, GetActorLocation(), GetActorRotation());
		}
	}
	if (LaunchSound) {
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, GetActorLocation());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No sound for hit assigned. aka [HitSound] in Projectile"));
	}
	
	if (CamShake) {
		if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0)) {
			PC->ClientStartCameraShake(CamShake);
		}
	}

	this->Destroy();
}



