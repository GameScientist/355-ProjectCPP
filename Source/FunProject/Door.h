// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "InteractableThing.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Door.generated.h"

class USceneComponent;

UCLASS()
class FUNPROJECT_API ADoor : public AActor, public IInteractableThing
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ADoor();

	// scene component for root
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	class USceneComponent* TheRoot;

	// scene component for root
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USceneComponent* TheHinge;

	// scene component for hinge
	// mesh for door
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* TheMeshDoor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* Collider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UInstancedStaticMeshComponent* TheMeshFrame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Stuff")
	UCurveFloat* doorOpenCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Stuff")
	float WidthOfDoor = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Stuff")
	float HeightOfDoor = 300;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Stuff")
	float DepthOfDoor = 25;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTimelineComponent* DoorAnim;

	bool IsDoorFlipped = false;
	bool IsDoorOpen = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform &xform) override;
	UFUNCTION()
	void OnAnimUpdate(float val);
	void Interact();
};
