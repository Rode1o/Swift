// Fill out your copyright notice in the Description page of Project Settings.
#include "Ball.h"


// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Use a sphere as a simple collision representation
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionSphere->SetSimulatePhysics(true);
	CollisionSphere->InitSphereRadius(16.f);
	CollisionSphere->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionSphere->OnComponentHit.AddDynamic(this, &ABall::OnCompHit);

	// Projecticle setting
	PhysicComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Physic"));
	PhysicComponent->UpdatedComponent = CollisionSphere;
	PhysicComponent->InitialSpeed = 0.f;
	PhysicComponent->MaxSpeed = 300.f;
	PhysicComponent->bRotationFollowsVelocity = true;
	PhysicComponent->bShouldBounce = true;

	RootComponent = CollisionSphere;
}


void ABall::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 300.f, GetActorLocation());
	}
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

