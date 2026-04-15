// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TerminalDeviceInterface.h"
#include "CommandRecieverBASE.generated.h"

class AComandManager;

UCLASS(Abstract)
class BUNKER_API ACommandRecieverBASE : public AActor, public ITerminalDeviceInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACommandRecieverBASE();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	AComandManager* CommandManager;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FName> AllowedCommands;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DeviceID;
};
