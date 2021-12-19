// Fill out your copyright notice in the Description page of Project Settings.


#include "TeamPlayerController.h"

ATeamPlayerController::ATeamPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	TeamId = FGenericTeamId(10);
}

FGenericTeamId ATeamPlayerController::GetGenericTeamId() const
{
	return TeamId;
}
