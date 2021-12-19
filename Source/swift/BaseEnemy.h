// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "STS_PatrolActor.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "BaseEnemy.generated.h"

UENUM(BlueprintType)
enum class E_EnemyStatus : uint8
{
	EnemyStatus_Patrol = 0 UMETA(DisplayName="Patrol"),
	EnemyStatus_Searching = 1 UMETA(DisplayName="Searching"),
	EnemyStatus_Alert = 2 UMETA(DisplayName="Alert"),
};

class ASTS_PatrolActor;


UCLASS()
class SWIFT_API ABaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemy();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ASTS_PatrolActor* PatrolActorReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TMap<E_EnemyStatus, float> EnemySpeedMap;
	
	UFUNCTION(BlueprintCallable)
	void SetEnemyStatus(E_EnemyStatus NewEnemyStatus);
	
	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category="Item")
	void TakeDown(class UCharacterMovementComponent* CharacterMovementComponent) ;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void BP_SetEnemyStatus(E_EnemyStatus NewEnemyStatus);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= Collision, meta=(AllowPrivateAccess = "true"))
		class UBoxComponent* CollisionBox;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	
};
