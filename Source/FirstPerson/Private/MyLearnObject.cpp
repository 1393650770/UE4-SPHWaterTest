// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLearnObject.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <FirstPerson/FirstPersonCharacter.h>

// Sets default values
AMyLearnObject::AMyLearnObject()
{

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetupAttachment(MeshComp);
	

}

// Called when the game starts or when spawned
void AMyLearnObject::BeginPlay()
{
	Super::BeginPlay();
	//PlayEffects();

}

void AMyLearnObject::PlayEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, PlayerEX, GetActorLocation());

}



void AMyLearnObject::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	PlayEffects();
	AFirstPersonCharacter* MyCharater = Cast<AFirstPersonCharacter>(OtherActor);
	if (MyCharater)
	{
		MyCharater->bIsCarryByInObjective = true;
		Destroy();
	}
}

