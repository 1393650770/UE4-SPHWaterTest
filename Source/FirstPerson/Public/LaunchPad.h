// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaunchPad.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UParticleSystem;
UCLASS()
class FIRSTPERSON_API ALaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaunchPad();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp ;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* OverlapComp ;

	UFUNCTION()
	void OverlapLaunchPad(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
	float LaunchStrength=1500.0f;

	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
	float LaunchPitchAngle = 40.0f;
	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
	UParticleSystem* ActivateLaunchPadEffect;

public:	

};
