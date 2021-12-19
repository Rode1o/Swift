// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "TeamPlayerController.generated.h"

class ATeamPlayerController;


/**
 * 
 */
UCLASS()
class SWIFT_API ATeamPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATeamPlayerController();

private: 
	// Implement The Generic Team Interface 
	FGenericTeamId TeamId;
	FGenericTeamId GetGenericTeamId() const;
	
};
