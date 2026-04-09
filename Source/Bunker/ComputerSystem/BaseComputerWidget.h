// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseComputerWidget.generated.h"

class AComputerActor;

/**
 * 
 */
UCLASS()
class BUNKER_API UBaseComputerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void Init(class AComputerActor* InTerminal);

	UFUNCTION(BlueprintCallable)
	void SendCommand(FName Command, FName CommandTarget);

private:

	UPROPERTY()
	AComputerActor* Terminal;
};
