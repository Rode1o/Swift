// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "STS_PatrolActor.generated.h"

class USplineComponent;

UCLASS()
class SWIFT_API ASTS_PatrolActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTS_PatrolActor();
	USplineComponent* SplineComponent;

	UFUNCTION(BlueprintCallable)
	FVector GetWorldLocationByIndex(const int32 Index) const;

	UFUNCTION(BlueprintCallable)
	int32 GetLastIndex() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
