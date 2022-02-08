// Copyright Epic Games, Inc. All Rights Reserved.

#include "FirstPersonGameMode.h"
#include "FirstPersonHUD.h"
#include "FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "FirstPerson.h"
#include <Kismet/GameplayStatics.h>


AFirstPersonGameMode::AFirstPersonGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFirstPersonHUD::StaticClass();


}


void AFirstPersonGameMode::CompleteMission(APawn* InstigatorPawn)
{
	if (InstigatorPawn)
	{
		InstigatorPawn->DisableInput(nullptr);

		if (SpectatingViewpoint)
		{
			TArray<AActor*> ReturnedActors;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpoint, ReturnedActors);

			if (ReturnedActors.Num() > 0)
			{
				AActor* NewViewTarget = ReturnedActors[0];

				APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());
				if (PC)
				{
					PC->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Warning:SpectatingViewpoint is nullptr!"));
		}
	}

	OnMissionCompleted(InstigatorPawn);

}
