// Fill out your copyright notice in the Description page of Project Settings.


#include "ComandManager.h"
#include "TerminalCommand.h"
#include "TerminalDeviceInterface.h"

// Sets default values
AComandManager::AComandManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AComandManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AComandManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AComandManager::RegisterDevice(FName ID, AActor* Device)
{
	Devices.FindOrAdd(ID).Add(Device);
}

void AComandManager::UnregisterDevice(FName ID)
{
	Devices.Remove(ID);
}

void AComandManager::ExecuteCommand(const FTerminalCommand& Cmd)
{
	GEngine->AddOnScreenDebugMessage(-1, 7.f, FColor::Green, FString::Printf(TEXT("Executing: %s to %s"), *Cmd.Command.ToString(), *Cmd.Target.ToString()));

	if (TArray<AActor*>* Found = Devices.Find(Cmd.Target))
	{
		for (AActor* Device : *Found)
		{
			ITerminalDeviceInterface::Execute_OnTerminalCommand(Device, Cmd.Command);
		}
	}
}

