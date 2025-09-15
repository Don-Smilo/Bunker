// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include <InputMappingContext.h>
#include "DefaultPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BUNKER_API ADefaultPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* CurrentMappingContext;
	
};
