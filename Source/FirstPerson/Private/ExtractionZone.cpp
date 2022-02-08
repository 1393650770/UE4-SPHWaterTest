// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtractionZone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include <FirstPerson/FirstPersonCharacter.h>
#include <FirstPerson/FirstPersonGameMode.h>
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>



// Sets default values
AExtractionZone::AExtractionZone()
{


	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComponent"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(200.0f));
	RootComponent = OverlapComp;
	OverlapComp->SetHiddenInGame(false);
	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AExtractionZone::HandleOverlap);

	DecalComp= CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	DecalComp->DecalSize = FVector(200.0f);

}



void AExtractionZone::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	

	AFirstPersonCharacter* MyPawn = Cast<AFirstPersonCharacter>(OtherActor);
	if (MyPawn==nullptr)
	{
		return;
	}

	if (MyPawn->bIsCarryByInObjective)
	{
		AFirstPersonGameMode* GameMode=Cast<AFirstPersonGameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->CompleteMission(MyPawn);
		}
		UE_LOG(LogTemp, Log, TEXT("Have get Extraction"));

		Destroy();
	}
	else
	{
		UGameplayStatics::PlaySound2D(this, ObjectMissionSound);
	}

	
}


