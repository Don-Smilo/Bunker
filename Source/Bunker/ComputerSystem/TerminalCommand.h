#pragma once

#include "CoreMinimal.h"
#include "TerminalCommand.generated.h"

USTRUCT(BlueprintType)
struct FTerminalCommand
{
	GENERATED_BODY()

	UPROPERTY()
	FName Command;

	UPROPERTY()
	FName Target;
};