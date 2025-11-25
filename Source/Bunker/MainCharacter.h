// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <EnhancedInputLibrary.h>
#include "MainCharacter.generated.h"

class UInputComponent;
class UInventoryComponent;
class UItemDataAsset;

UCLASS()
class BUNKER_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* CurrentMappingContext;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FlashlightAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta =(AllowPrivateAccess="true"))
	class UInputAction* InspectRotationAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta =(AllowPrivateAccess="true"))
	class UInputAction* InspectScaleAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta =(AllowPrivateAccess="true"))
	class UInputAction* InspectCollectAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ShowInventoryAction;

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Flashlight")
	void SwitchFlashlight();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flashlight")
	bool bFlashlightIsOn;


	void Interact();

	void CheckInteract();


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool bIsInInteraction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	bool bIsInInspection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	bool bIsInFocus;
	
	AActor* ActorToInteract;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool bCanInteract;

	EInteractionType InteractionType;


	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Inspection")
	void Inspect(AActor* ActorToInspect);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Inspection")
	void RotateInspectableItem(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Inspection")
	void ScaleInspectableItem(const FInputActionValue& Value);

	//UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Inspection")
	void Collect();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Focus")
	void Focus(AActor* ActorToFocus);


	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "UI")
	void ShowInventory();
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "UI")
	void HideInventory();

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	EInteractionType GetInteractionType();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	UInventoryComponent* Inventory;
};
