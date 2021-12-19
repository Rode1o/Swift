// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerStatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SWIFT_API UPlayerStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerStatComponent();

protected:
	UPROPERTY(VisibleAnywhere)
	float Stamina;

	FTimerHandle StaminaHandler;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void RegenerateStamina();
	

public:
	float GetStamina();
	void LowerStamina(float Value);
	void ControlSprintingTimer(bool IsSprinting);
};
