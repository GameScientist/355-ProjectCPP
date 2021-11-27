// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"
#include "Components/BoxComponent.h"

// Sets default values
ATarget::ATarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("trigger"));
	trigger->InitBoxExtent(FVector(100, 100, 100));
	trigger->SetCollisionProfileName("Trigger");
	RootComponent = trigger;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(FName("TheRoot"));
	Body->SetupAttachment(trigger);
	ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/Art/Meshes/1M_Cube"));
	Body->SetStaticMesh(Mesh.Object);

	trigger->OnComponentBeginOverlap.AddDynamic(this, & ATarget::OnOverlap);
}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATarget::OnOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, "I've been hit!");
	Destroy();
}
