// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TerminalDeviceInterface.generated.h"

struct FTerminalCommand;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTerminalDeviceInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BUNKER_API ITerminalDeviceInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
	void OnTerminalCommand(FName Command);
};
