// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventoryComponent::AddItem(UItemDataAsset* NewItem)
{
	if (!NewItem)
	{
		return false;
	}

	for (UItemDataAsset* Item : Items)
	{
		if (Item && Item->ItemID == NewItem->ItemID)
		{
			return false;
		}
	}

	Items.Add(NewItem);
	return true;
}

bool UInventoryComponent::RemoveItem(UItemDataAsset* ItemToRemove)
{
	if (!ItemToRemove)
	{
		return false;
	}

	int32 Removed = Items.Remove(ItemToRemove);
	return Removed > 0;
}

bool UInventoryComponent::HasItem(UItemDataAsset* ItemToFind)
{
	if (!ItemToFind)
	{
		return false;
	}

	for (UItemDataAsset* Item : Items)
	{
		if (Item && Item->ItemID == ItemToFind->ItemID)
		{
			return true;
		}
	}
	return false;
}

