#include "AFPSProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"


AFPSProjectile::AFPSProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFPSProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}