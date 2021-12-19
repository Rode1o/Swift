// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "mainCharacter.generated.h"

UCLASS()
class SWIFT_API AmainCharacter : public ACharacter
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
		class USpringArmComponent* BoomArmComponent;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
		class UCameraComponent * CameraComponent;



public:
	// Sets default values for this character's properties
	AmainCharacter();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	bool CanTakedown = false;

	class UPlayerStatComponent* PlayerStatComp; // pointer to PlayerStats

protected:
	
	bool bIsSprinting;
	FTimerHandle SprintingHandle; // Tick to handle the deal on stamina Bar

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void HandleSprinting();

	// Movement Character
	UFUNCTION()
		void Sprint();

	UFUNCTION()
		void Walk();
	
	UFUNCTION(BlueprintPure)
		float ReturnPlayerStat(); // Call to player stat Stamina
	

	UPROPERTY(EditAnywhere)
		float WalkingSpeed;
	
	UPROPERTY(EditAnywhere)
	float RunningSpeed;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
