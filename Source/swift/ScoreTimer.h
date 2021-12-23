// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "ScoreTimer.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class SWIFT_API UScoreTimer : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* TimerProgressBar;
};
