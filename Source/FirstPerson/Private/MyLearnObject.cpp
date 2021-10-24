// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLearnObject.h"
#include "Components/SphereComponent.h"
// Sets default values
AMyLearnObject::AMyLearnObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetupAttachment(MeshComp);
}

// Called when the game starts or when spawned
void AMyLearnObject::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyLearnObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

