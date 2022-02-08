// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHole.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	InnerSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphereComp"));
	OuterSphereComp= CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphereComp"));

	RootComponent = MeshComp;
	InnerSphereComp->SetupAttachment(MeshComp);
	OuterSphereComp->SetupAttachment(MeshComp);

	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	InnerSphereComp->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::OverlapInnerSphere);

	InnerSphereComp->SetSphereRadius(100);
	OuterSphereComp->SetSphereRadius(3000);


}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	TArray<UPrimitiveComponent*> OverlappingComps;
	OuterSphereComp->GetOverlappingComponents(OverlappingComps);

	for (int32 i = 0; i < OverlappingComps.Num(); i++)
	{
		UPrimitiveComponent* Primitive = OverlappingComps[i];
		if (Primitive && Primitive->IsSimulatingPhysics())
		{
			const float SphereRadius = OuterSphereComp->GetScaledSphereRadius();
			const float ForceStrength = -2000;
			Primitive->AddRadialForce(GetActorLocation(), SphereRadius, ForceStrength, ERadialImpulseFalloff::RIF_Constant, true);
		}
	}
}


void ABlackHole::OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		OtherActor->Destroy();
	}
}
