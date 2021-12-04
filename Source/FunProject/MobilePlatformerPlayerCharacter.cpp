// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Controller.h"
#include "MobilePlatformerPlayerCharacter.h"

// Sets default values
AMobilePlatformerPlayerCharacter::AMobilePlatformerPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AMobilePlatformerPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMobilePlatformerPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	OnStartCrouch(25, 25);
}

// Called to bind functionality to input
void AMobilePlatformerPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMobilePlatformerPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMobilePlatformerPlayerCharacter::MoveRight);
}


void AMobilePlatformerPlayerCharacter::MoveForward(float Value)
{
	if (Controller != nullptr)
	{
		if (Value > 0.0f) {
			ACharacter::Jump();
			GetCharacterMovement()->bWantsToCrouch = false;
			ACharacter::GetMesh()->SetRelativeScale3D(FVector(2, 2, 4));
			ACharacter::GetMesh()->SetRelativeLocation(FVector(0, 0, -50));
		}
		else if (Value < 0.0f) {
			ACharacter::StopJumping();
			GetCharacterMovement()->bWantsToCrouch = true;
			ACharacter::GetMesh()->SetRelativeScale3D(FVector(2, 2, 2));
			ACharacter::GetMesh()->SetRelativeLocation(FVector(0, 0, -25));
		}
		else {
			ACharacter::StopJumping();
			GetCharacterMovement()->bWantsToCrouch = false;
			ACharacter::GetMesh()->SetRelativeScale3D(FVector(2, 2, 4));
			ACharacter::GetMesh()->SetRelativeLocation(FVector(0, 0, -50));
		}
	}
}

void AMobilePlatformerPlayerCharacter::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0)
	{
		if (Value > 0.0f) {
			GetController()->ClientSetRotation(FRotator(0, 90, 0));
		}
		else if (Value < 0.0f) {
			GetController()->ClientSetRotation(FRotator(0, -90, 0));
		}
		AddMovementInput(FVector(0, Value, 0));
	}
}
