// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <EnhancedInputLibrary.h>
#include "MainCharacter.generated.h"

class UInputComponent;

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

	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Interaction")
	void Inspect(AActor* ActorToInspect);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Interaction")
	void RotateInspectableItem(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Interaction")
	void ScaleInspectableItem(const FInputActionValue& Value);


	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Interaction")
	void Focus(AActor* ActorToFocus);
};
