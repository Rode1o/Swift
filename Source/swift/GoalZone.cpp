// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalZone.h"

#include "mainCharacter.h"

// Sets default values
AGoalZone::AGoalZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereRadius = 66.f;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereCollision->InitSphereRadius(SphereRadius);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SphereCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereCollision->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	SphereCollision->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	SphereCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = SphereCollision;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AGoalZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGoalZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGoalZone::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if(IsValid(OtherActor))
	{
		AmainCharacter* OverlapActor = Cast<AmainCharacter>(OtherActor);
		if(IsValid(OverlapActor))
		{
			OverlapActor->CanScore = true;
//			UE_LOG(LogTemp, Warning, TEXT("Start Overlaping"));
		}
	}
}

void AGoalZone::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	if(IsValid(OtherActor))
	{
		AmainCharacter* OverlapActor = Cast<AmainCharacter>(OtherActor);
		if(IsValid(OverlapActor))
		{
			OverlapActor->CanScore = false;
//			UE_LOG(LogTemp, Warning, TEXT("End OVerlaping"));
		}
	}
}

