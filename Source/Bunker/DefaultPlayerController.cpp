// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerController.h"
#include <EnhancedInputSubsystems.h>

void ADefaultPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem< UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (Subsystem)
	{
		Subsystem->AddMappingContext(CurrentMappingContext, 0);
	}
}
