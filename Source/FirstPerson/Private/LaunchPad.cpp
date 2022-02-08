// Fill out your copyright notice in the Description page of Project Settings.


#include "LaunchPad.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Character.h>
// Sets default values
ALaunchPad::ALaunchPad()
{
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = OverlapComp;
	OverlapComp->SetBoxExtent(FVector(75, 75, 50));
	MeshComp->SetupAttachment(RootComponent);

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &ALaunchPad::OverlapLaunchPad);
}

void ALaunchPad::OverlapLaunchPad(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FRotator LaunchDirection = GetActorRotation();
	LaunchDirection.Pitch += LaunchPitchAngle;
	FVector LaunchVelocity = LaunchDirection.Vector() * LaunchStrength;
	ACharacter* OtherCharater = Cast<ACharacter>(OtherActor);
	if (OtherCharater)
	{
		OtherCharater->LaunchCharacter(LaunchVelocity, true, true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ActivateLaunchPadEffect, GetActorLocation());
	}
	else if(OtherActor&&OtherComp->IsSimulatingPhysics())
 	{
		OtherComp->AddImpulse(LaunchVelocity, NAME_None, true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ActivateLaunchPadEffect, GetActorLocation());
	}
}
