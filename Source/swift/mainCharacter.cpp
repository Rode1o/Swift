// Fill out your copyright notice in the Description page of Project Settings.

#include "mainCharacter.h"
#include "PlayerStatComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "TimerManager.h"


// Sets default values
AmainCharacter::AmainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(34.f, 55.0f);

	// Camera and Spring Arm

	BoomArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera boom"));
	BoomArmComponent->SetupAttachment(RootComponent);
	BoomArmComponent->TargetArmLength = 300.f;
	BoomArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(BoomArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// Character Movements

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 540, 0);

	// Variables
	
	RunningSpeed = 1200.f;
	WalkingSpeed = 600.f;
	bIsSprinting = false;

	// Player Stat Component
	PlayerStatComp = CreateDefaultSubobject<UPlayerStatComponent>("PlayerStatComponent");
}


// Called when the game starts or when spawned
void AmainCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(SprintingHandle, this, &AmainCharacter::HandleSprinting, 1.0f, true);	
	
}
// Called every frame
void AmainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsScoring)
	{
		fTimeScoring += DeltaTime;
	}
}

// Called to bind functionality to input
void AmainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward/Backward", this, &AmainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight/Left", this,&AmainCharacter::MoveRight);
	PlayerInputComponent->BindAxis("lookRight/Left", this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("lookUp/Down", this,&APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AmainCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AmainCharacter::Walk);
	PlayerInputComponent->BindAction("Hold", IE_Pressed, this, &AmainCharacter::HoldDown);
	PlayerInputComponent->BindAction("Hold", IE_Released, this, &AmainCharacter::HoldUp);

}

void AmainCharacter::MoveForward(float Value)
{
	if(Controller != NULL && Value != 0.0)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator Yaw(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);
		if(!bIsSprinting)
			Value *= 0.5f;
		AddMovementInput(Direction, Value);
	}
}

void AmainCharacter::MoveRight(float Value)
{
	if(Controller != NULL && Value != 0.0)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator Yaw(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y);
		if(!bIsSprinting)
			Value *= 0.5f;
		AddMovementInput(Direction, Value);
	}
}


void AmainCharacter::Sprint()
{
	if(PlayerStatComp->GetStamina() > 50.0f)
	{
		bIsSprinting = true;
		PlayerStatComp->ControlSprintingTimer(true);
	}
	else if (PlayerStatComp->GetStamina() <= 0.f)
	{
		PlayerStatComp->ControlSprintingTimer(false);
		GetCharacterMovement()->MaxWalkSpeed = RunningSpeed ;
	}
}

void AmainCharacter::Walk()
{
	bIsSprinting = false;
	PlayerStatComp->ControlSprintingTimer(false);
	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
}

void AmainCharacter::HandleSprinting() // Set the ticks to devalue the Stamina
{
	if (bIsSprinting)
	{
		PlayerStatComp->LowerStamina(20.f);
		if(PlayerStatComp->GetStamina() <= 0.f)
			Walk();
	}
}


float AmainCharacter::ReturnPlayerStat()
{
	return PlayerStatComp->GetStamina();
}


void AmainCharacter::HoldDown()
{
	if(CanScore)
	{
		bIsScoring = true;
	}
	
}

void AmainCharacter::HoldUp()
{
	if(CanScore)
	{
		bIsScoring = false;

		if(fTimeScoring > 2)
		{
			UE_LOG(LogTemp, Warning, TEXT("Scoring... After 2 Hold Seconds"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Can't Score"));
		}
		fTimeScoring = 0.f;
	}
}



