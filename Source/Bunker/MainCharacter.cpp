// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetSystemLibrary.h"

#include "InteractableInterface.h"
#include "CollectableInterface.h"
#include "InventoryComponent.h"
#include "ItemDataAsset.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bFlashlightIsOn = false;

	bIsInInteraction = false;
	bCanInteract = false;
	InteractionType = EInteractionType::None;


	bIsInInspection = false;
	bIsInFocus = false;

	ActorToInteract = nullptr;

	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));

	IntractionIgnoredActors.Add(this);
	InteractionTraceType = UEngineTypes::ConvertToTraceType(ECC_Visibility);
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(CurrentMappingContext, 0);
		}
	}
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckInteract();

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainCharacter::Look);

		EnhancedInputComponent->BindAction(FlashlightAction, ETriggerEvent::Triggered, this, &AMainCharacter::SwitchFlashlight);
		
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AMainCharacter::Interact);
		EnhancedInputComponent->BindAction(InspectRotationAction, ETriggerEvent::Triggered, this, &AMainCharacter::RotateInspectableItem);
		EnhancedInputComponent->BindAction(InspectScaleAction, ETriggerEvent::Triggered, this, &AMainCharacter::ScaleInspectableItem);
		EnhancedInputComponent->BindAction(InspectCollectAction, ETriggerEvent::Triggered, this, &AMainCharacter::Collect);
		EnhancedInputComponent->BindAction(InspectEscapeAction, ETriggerEvent::Triggered, this, &AMainCharacter::Interact);
		EnhancedInputComponent->BindAction(FocusEscapeAction, ETriggerEvent::Triggered, this, &AMainCharacter::Interact);
		
		
		EnhancedInputComponent->BindAction(ShowInventoryAction, ETriggerEvent::Started, this, &AMainCharacter::ShowInventory);
		EnhancedInputComponent->BindAction(ShowInventoryAction, ETriggerEvent::Completed, this, &AMainCharacter::HideInventory);

		EnhancedInputComponent->BindAction(PauseMenuAction, ETriggerEvent::Triggered, this, &AMainCharacter::PauseGame);

	}
}

void AMainCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	 
	if (GetController())
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AMainCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerPitchInput(LookAxisVector.Y);
		AddControllerYawInput(LookAxisVector.X);
	}
}

void AMainCharacter::Interact()
{
	if (ActorToInteract != nullptr)
	{
		switch (InteractionType)
		{
		case EInteractionType::Blocked:
		{
			UItemDataAsset* RequiredItem = IInteractableInterface::Execute_GetRequestedItem(ActorToInteract);

			if (Inventory->HasItem(RequiredItem))
			{
				IInteractableInterface::Execute_Unlock(ActorToInteract);
				Inventory->RemoveItem(RequiredItem);
			}

			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("No requred item"));
			}
		}
			break;


		case EInteractionType::Toggle:

			IInteractableInterface::Execute_StartInteract(ActorToInteract, this);
			
			break;


		case EInteractionType::Focus:
		case EInteractionType::Inspect:
			
			if (!bIsInInteraction)
			{
				IInteractableInterface::Execute_StartInteract(ActorToInteract, this);

				bCanInteract = false;
				bIsInInteraction = true;
			}

			else
			{
				IInteractableInterface::Execute_StopInteract(ActorToInteract, this);
				bIsInInteraction = false;
			}

			break;


		case EInteractionType::None:
			break;


		default:
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UNEXPECTED INTERACTION TYPE"));
			break;
		}
	}
}

void AMainCharacter::CheckInteract()
{
	if (!bIsInInteraction) {

		FVector ViewLocation;
		FRotator ViewRotation;

		GetController()->GetPlayerViewPoint(ViewLocation, ViewRotation);

		FVector TraceStart = ViewLocation;
		FVector TraceEnd = TraceStart + (ViewRotation.Vector() * InteractionTraceDistance);

		FHitResult HitResult;

		bool bHit = UKismetSystemLibrary::SphereTraceSingle(
			GetWorld(),
			TraceStart, TraceEnd, InteractionTraceRadius,
			InteractionTraceType, false, IntractionIgnoredActors, 
			EDrawDebugTrace::None, HitResult, true
		);

		if (bHit && HitResult.GetActor())
		{
			AActor* HitActor = HitResult.GetActor();

			if (HitActor->Implements<UInteractableInterface>())
			{
				ActorToInteract = HitActor;
				bCanInteract = IInteractableInterface::Execute_GetCanInteract(ActorToInteract);
				InteractionType = IInteractableInterface::Execute_GetInteractionType(ActorToInteract);
			}

			else
			{
				ActorToInteract = nullptr;
				bCanInteract = false;
				InteractionType = EInteractionType::None;
				
			}
		}

		else
		{
			ActorToInteract = nullptr;
			bCanInteract = false;
			InteractionType = EInteractionType::None;
		}
	}

	else
	{
		bCanInteract = false;
		InteractionType = EInteractionType::None;
	}

}

void AMainCharacter::Collect()
{
	if (ActorToInteract)
	{
		if (ActorToInteract->Implements<UCollectableInterface>())
		{
			if (Inventory->AddItem(ICollectableInterface::Execute_GetItemData(ActorToInteract)))
			{
				ICollectableInterface::Execute_OnCollect(ActorToInteract, this);
				bIsInInteraction = false;
			}

		}
	}
}

EInteractionType AMainCharacter::GetInteractionType()
{
	return InteractionType;
}
