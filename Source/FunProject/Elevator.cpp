// Fill out your copyright notice in the Description page of Project Settings.


#include "Elevator.h"
#include "Components/BoxComponent.h"

// Sets default values
AElevator::AElevator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GoingUp = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Switch = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Switch"));
	Switch->SetupAttachment(Root);

	Platform = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform"));
	Platform->SetupAttachment(Switch);

	ConstructorHelpers::FObjectFinder<UStaticMesh> TheCubeMesh(TEXT("/Game/Art/Meshes/1M_Cube"));
	if (TheCubeMesh.Object) {
		Switch->SetStaticMesh(TheCubeMesh.Object);
		Platform->SetStaticMesh(TheCubeMesh.Object);
	}

}

// Called when the game starts or when spawned
void AElevator::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GoingUp && Platform->GetRelativeLocation().Z < 50) {
		Platform->AddRelativeLocation(Platform->GetUpVector() * DeltaTime * 100);
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, "Player interacted with object.");
	}
}

void AElevator::OnConstruction(const FTransform& xform) {
	Super::OnConstruction(xform);
	Switch->SetRelativeLocation(FVector(0, 0, 100));
	Switch->SetWorldScale3D(FVector(0.1, 2, 2));
	Platform->SetRelativeLocation(FVector(0,0,-50));
	Platform->SetWorldScale3D(FVector(2, 2, 0.1f));
}

void AElevator::Interact() {
	GoingUp = true;
}

