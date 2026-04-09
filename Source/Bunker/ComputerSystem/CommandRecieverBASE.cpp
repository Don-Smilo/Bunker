// Fill out your copyright notice in the Description page of Project Settings.


#include "CommandRecieverBASE.h"
#include <Kismet/GameplayStatics.h>
#include "ComandManager.h"

// Sets default values
ACommandRecieverBASE::ACommandRecieverBASE()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACommandRecieverBASE::BeginPlay()
{
	Super::BeginPlay();

	AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AComandManager::StaticClass());
	
	CommandManager = Cast<AComandManager>(FoundActor);

	if (!CommandManager)
		return;

	if (DeviceID.IsNone())
		return;

	CommandManager->RegisterDevice(DeviceID, this);
}

// Called every frame
void ACommandRecieverBASE::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

