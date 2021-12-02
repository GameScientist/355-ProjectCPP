// Fill out your copyright notice in the Description page of Project Settings.


#include "Elevator.h"

// Sets default values
AElevator::AElevator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	RootComponent = Root;

	Switch = CreateDefaultSubobject<UStaticMeshComponent>(FName("Switch"));
	Switch->SetupAttachment(Root);

	Platform = CreateDefaultSubobject<UStaticMeshComponent>(FName("Platform"));
	Platform->SetupAttachment(Switch);

	ElevatorAnim = CreateDefaultSubobject<UTimelineComponent>(FName("Elevator raise timeline."));

	ConstructorHelpers::FObjectFinder<UStaticMesh> TheCubeMesh(TEXT("/Game/Art/Meshes/1M_Cube"));
	if (TheCubeMesh.Object) {
		Switch->SetStaticMesh(TheCubeMesh.Object);
		Platform->SetStaticMesh(TheCubeMesh.Object);
	}

}

void AElevator::OnAnimUpdate(float val) {
	Platform->SetRelativeLocation(FVector(0, 0, val*100-50));
}

// Called when the game starts or when spawned
void AElevator::BeginPlay()
{
	Super::BeginPlay();
	if (ElevationCurve)
	{
		FOnTimelineFloat eventHandler;
		eventHandler.BindUFunction(this, TEXT("OnAnimUpdate"));
		//eventHandler.BindDynamic(this, &ADoor::OnAnimUpdate);
		ElevatorAnim->AddInterpFloat(ElevationCurve, eventHandler, FName("Handle curve func"));
		ElevatorAnim->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
	}
}

// Called every frame
void AElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AElevator::OnConstruction(const FTransform& xform) {
	Super::OnConstruction(xform);
	Switch->SetRelativeLocation(FVector(0, 0, 100));
	Switch->SetWorldScale3D(FVector(0.1, 2, 2));
	Platform->SetRelativeLocation(FVector(0, 0, -50));
	Platform->SetWorldScale3D(FVector(2, 2, 0.1f));
}

void AElevator::Interact() {
	if (Elevated) {
		ElevatorAnim->Reverse();
		Elevated = false;
	}
	else {
		ElevatorAnim->Play();
		Elevated = true;
	}
}

