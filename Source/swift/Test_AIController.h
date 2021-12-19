// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GenericTeamAgentInterface.h"
#include "Test_AIController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SWIFT_API ATest_AIController : public AAIController
{
	GENERATED_BODY()
	ATest_AIController();

public:
	// Override this function 
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	UFUNCTION(BlueprintCallable)
	ETeamAttitude::Type GetAttitudeTowards(const AActor* Other) const;
	
};
