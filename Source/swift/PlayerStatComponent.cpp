// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatComponent.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Engine/Engine.h"

// Sets default values for this component's properties
UPlayerStatComponent::UPlayerStatComponent()
{
	Stamina = 100.0f;
}

// Called when the game starts
void UPlayerStatComponent::BeginPlay()
{
	Super::BeginPlay();
	//SetIsReplicated(true);

	GetWorld()->GetTimerManager().SetTimer(StaminaHandler, this, &UPlayerStatComponent::RegenerateStamina, 1.0f, true);
}


void UPlayerStatComponent::LowerStamina(float Value)
{
	Stamina -= Value;
}

void UPlayerStatComponent::RegenerateStamina()
{
	if(Stamina >= 100)
		Stamina = 100.f;
	else
		Stamina += 10 ;
}

float UPlayerStatComponent::GetStamina()
{
	return Stamina;
}


void UPlayerStatComponent::ControlSprintingTimer(bool IsSprinting)
{
	if(IsSprinting)
	{
		GetWorld()->GetTimerManager().PauseTimer(StaminaHandler);
	}
	else
	{
		GetWorld()->GetTimerManager().UnPauseTimer(StaminaHandler);
	}
}

