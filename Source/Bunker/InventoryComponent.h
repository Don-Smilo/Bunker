// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemDataAsset.h"
#include "InventoryComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemAdded, UItemDataAsset*, AddedItem, int, Index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemRemoved, int, Index);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUNKER_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(UItemDataAsset* NewItem);
		
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItem(UItemDataAsset* Item);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool HasItem(UItemDataAsset* Item);

	int GetItemIndex(UItemDataAsset* Item);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory")
	TArray<UItemDataAsset*> GetItems();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory")
	int GetInventorySize();


private:

	TArray<UItemDataAsset*> Items;

	int InventorySize;


public:
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnItemAdded OnItemAdded;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnItemRemoved OnItemRemoved;


};
