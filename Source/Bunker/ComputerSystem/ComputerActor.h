// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bunker/InteractableInterface.h"
#include "ComputerActor.generated.h"

struct FTerminalCommand;
class AComandManager;
class UBaseComputerWidget;
class UWidgetComponent;

UCLASS()
class BUNKER_API AComputerActor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AComputerActor();

	void HandleCommand(const FTerminalCommand& Cmd);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY()
	AComandManager* CommandManager;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UBaseComputerWidget> WidgetClass;

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* ScreenWidget;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
