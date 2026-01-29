// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ComputerScreenWidget0.generated.h"

class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorActivated);

/**
 * 
 */
UCLASS()
class BUNKER_API UComputerScreenWidget0 : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;


protected:
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, Category = "ComputerUI")
	UButton* UnlockDoorButton;

	//UFUNCTION()
	void OnUnlockButtonClicked();

private:
	UPROPERTY(BlueprintAssignable, Category = "ComputerUI")
	FOnDoorActivated OnDoorActivated;

};
