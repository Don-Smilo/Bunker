// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ComandManager.generated.h"

struct FTerminalCommand;

UCLASS()
class BUNKER_API AComandManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AComandManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void RegisterDevice(FName ID, AActor* Device);
	void UnregisterDevice(FName ID);

	void ExecuteCommand(const FTerminalCommand& Cmd);

private:

	TMap<FName, TArray<AActor*>> Devices;

};
