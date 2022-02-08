// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIGuard.generated.h"
class UPawnSensingComponent;

UENUM(BlueprintType)
enum class EAIState :uint8
{
	Idle,
	Suspicious,
	Alerted
};

UCLASS()
class FIRSTPERSON_API AAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere,Category="Components")
	UPawnSensingComponent* PawnSensingComp;

	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
	void OnPawnHeard(APawn* SeenPawn,const FVector& Location,float Volume);

	FRotator OriginalRotation;

	FTimerHandle TimerHandle_ResetOrientation;

	EAIState GuardState=EAIState::Idle;

	void SetGuardState(EAIState NewState);
	UFUNCTION(BlueprintImplementableEvent,Category= AI)
	void OnStateChanged(EAIState NewState);

	void ResetOrientation();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
