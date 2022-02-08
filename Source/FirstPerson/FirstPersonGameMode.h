// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FirstPersonGameMode.generated.h"

UCLASS(minimalapi)
class AFirstPersonGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly,Category="Spectating")
	TSubclassOf<AActor> SpectatingViewpoint;

public:
	AFirstPersonGameMode();

	void CompleteMission(APawn* InstigatorPawn);

	UFUNCTION(BlueprintImplementableEvent,Category = "GameMode")
	void OnMissionCompleted(APawn* InstigatorPawn);
};



