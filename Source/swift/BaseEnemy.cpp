// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"

#include "mainCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(34.f, 55.0f);
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackZone"));
	CollisionBox->SetupAttachment(this->GetMesh(),	 FName("AttackZone"));
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	CollisionBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	CollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 540, 0);

}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseEnemy::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if(IsValid(OtherActor))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Get1"));
		AmainCharacter* Overlapmain = Cast<AmainCharacter>(OtherActor);
		if(IsValid(Overlapmain))
		{
			Overlapmain->CanTakedown = true;
			//UE_LOG(LogTemp, Warning, TEXT("Get2"));
			//UE_LOG(LogTemp, Warning, TEXT("The boolean value is %s"), ( Overlapmain->CanTakedown ? TEXT("true") : TEXT("false") ));
		}
	}
	
}

void ABaseEnemy::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	if(IsValid(OtherActor))
	{
		AmainCharacter* Overlapmain = Cast<AmainCharacter>(OtherActor);
		if(IsValid(Overlapmain))
		{
			Overlapmain->CanTakedown = false;
			//UE_LOG(LogTemp, Warning, TEXT("The boolean value is %s"), ( Overlapmain->CanTakedown ? TEXT("true") : TEXT("false") ));
		}
	}
}


void ABaseEnemy::TakeDown_Implementation(UCharacterMovementComponent* CharacterMovementComponent)
{
	CharacterMovementComponent->SetMovementMode(EMovementMode::MOVE_None);
}

void ABaseEnemy::SetEnemyStatus(E_EnemyStatus NewEnemyStatus)
{
	float Speed = EnemySpeedMap[NewEnemyStatus];
	GetCharacterMovement()->MaxWalkSpeed = Speed;
	BP_SetEnemyStatus(NewEnemyStatus);
}