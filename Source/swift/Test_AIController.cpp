// Fill out your copyright notice in the Description page of Project Settings.


#include "Test_AIController.h"


ATest_AIController::ATest_AIController()
{
	SetGenericTeamId(FGenericTeamId(5));
}
ETeamAttitude::Type ATest_AIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (const APawn* OtherPawn = Cast<APawn>(&Other)) {

		if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
		{
			return Super::GetTeamAttitudeTowards(*OtherPawn->GetController());
		}
	}

	return ETeamAttitude::Hostile;
}

ETeamAttitude::Type ATest_AIController::GetAttitudeTowards(const AActor* Other) const
{
	return GetTeamAttitudeTowards(*Other);
}

