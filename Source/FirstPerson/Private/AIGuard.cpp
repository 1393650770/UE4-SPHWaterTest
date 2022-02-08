// Fill out your copyright notice in the Description page of Project Settings.


#include "AIGuard.h"
#include <FirstPerson/Public/AIGuard.h>
#include "Perception/PawnSensingComponent.h"
#include <Runtime/Experimental/Chaos/Public/Chaos/DebugDrawQueue.h>
#include <Runtime/Engine/Public/DrawDebugHelpers.h>
// Sets default values
AAIGuard::AAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AAIGuard::OnPawnSeen);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AAIGuard::OnPawnHeard);

}

// Called when the game starts or when spawned
void AAIGuard::BeginPlay()
{
	Super::BeginPlay();
	OriginalRotation = GetActorRotation();
}

void AAIGuard::OnPawnSeen(APawn* SeenPawn)
{
	if (SeenPawn == nullptr)
	{
		return;
	}
	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(),32.0f,12,FColor::Yellow,false,10.0f);
	SetGuardState(EAIState::Alerted);
}

void AAIGuard::OnPawnHeard(APawn* HearPawn, const FVector& Location, float Volume)
{
	if (GuardState == EAIState::Alerted)
		return;

	DrawDebugSphere(GetWorld(), HearPawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 10.0f);
	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();
	FRotator NewLookAt=  FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookAt.Pitch = 0;
	NewLookAt.Roll = 0;
	SetActorRotation(NewLookAt);
	GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
	GetWorldTimerManager().SetTimer(TimerHandle_ResetOrientation,this,&AAIGuard::ResetOrientation,3.0f);
	
	SetGuardState(EAIState::Suspicious);
}

void AAIGuard::SetGuardState(EAIState NewState)
{
	if (NewState == GuardState)
		return;
	GuardState = NewState;

	OnStateChanged(GuardState);
}

void AAIGuard::ResetOrientation()
{
	SetActorRotation(OriginalRotation);

	SetGuardState(EAIState::Idle);
}

// Called every frame
void AAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

