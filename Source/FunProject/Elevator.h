// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "InteractableThing.h"
#include "Elevator.generated.h"

UCLASS()
class FUNPROJECT_API AElevator : public AActor, public IInteractableThing
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AElevator();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* Switch;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* Platform;

	UPROPERTY(VisibleAnywhere)
	bool GoingUp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& xform) override;

	virtual void Interact();
};
