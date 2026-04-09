// Fill out your copyright notice in the Description page of Project Settings.


#include "ComputerActor.h"
#include "BaseComputerWidget.h"
#include "Components/WidgetComponent.h"
#include "ComandManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AComputerActor::AComputerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ComputerMesh"));

	ScreenWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Screen"));
	ScreenWidget->SetupAttachment(StaticMesh);
	ScreenWidget->SetWidgetSpace(EWidgetSpace::World);
	ScreenWidget->SetDrawSize(FVector2D(800.f, 600.f));

}

void AComputerActor::HandleCommand(const FTerminalCommand& Cmd)
{
	if (CommandManager)
	{
		CommandManager->ExecuteCommand(Cmd);
	}
}

// Called when the game starts or when spawned
void AComputerActor::BeginPlay()
{
	Super::BeginPlay();

	CommandManager = Cast<AComandManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AComandManager::StaticClass()));

	ScreenWidget->SetWidgetClass(WidgetClass);
	ScreenWidget->InitWidget();

	UBaseComputerWidget* Widget = Cast<UBaseComputerWidget>(ScreenWidget->GetUserWidgetObject());

	if (Widget)
	{
		Widget->Init(this);
	}
	
}

// Called every frame
void AComputerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

