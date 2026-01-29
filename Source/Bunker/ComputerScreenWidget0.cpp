// Fill out your copyright notice in the Description page of Project Settings.


#include "ComputerScreenWidget0.h"
#include "Components/Button.h"

void UComputerScreenWidget0::NativeConstruct()
{
	Super::NativeConstruct();

	if (UnlockDoorButton)
	{
		UnlockDoorButton->OnClicked.AddDynamic(this, &UComputerScreenWidget0::OnUnlockButtonClicked);


	}
}

void UComputerScreenWidget0::OnUnlockButtonClicked()
{
	OnDoorActivated.Broadcast();
}
