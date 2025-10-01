// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "InteractableInterface.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bFlashlightIsOn = false;
	bIsInInteraction = false;
	bCanInteract = false;

	ActorToInteract = nullptr;
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
		if (IInteractableInterface::Execute_GetInteractionType(ActorToInteract) == EInteractionType::Toggle)
		{
			IInteractableInterface::Execute_StartInteract(ActorToInteract, this);

			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Toggled"));
		}

		else
		{
			if (!bIsInInteraction)
			{
				IInteractableInterface::Execute_StartInteract(ActorToInteract, this);
				bCanInteract = false;
				bIsInInteraction = true;

				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Interaction started"));
			}

			else
			{
				IInteractableInterface::Execute_StopInteract(ActorToInteract, this);
				bIsInInteraction = false;
				
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Interaction stopped"));
			}
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
		FVector TraceEnd = TraceStart + (ViewRotation.Vector() * 100.f);

		FHitResult HitResult;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, Params);

		if (bHit && HitResult.GetActor())
		{
			AActor* HitActor = HitResult.GetActor();

			if (HitActor->Implements<UInteractableInterface>())
			{
				ActorToInteract = HitActor;
				bCanInteract = IInteractableInterface::Execute_GetCanInteract(ActorToInteract);
			}

			else
			{
				ActorToInteract = nullptr;
				bCanInteract = false;
			}
		}

		else
		{
			ActorToInteract = nullptr;
			bCanInteract = false;
		}
	}

	else
	{
		bCanInteract = false;
	}

}


