// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Containers/Array.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	IsDoorOpen = false;
	MassRequired = 50.0f;
	OpenAngle = -90.0f;
	DoorCloseDelay = 1.0f;
	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Owner = GetOwner();
}

void UOpenDoor::OpenDoor()
{
	IsDoorOpen = true;
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UOpenDoor::CloseDoor() {
	IsDoorOpen = false;
	Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (!IsDoorOpen && GetTotalMassOnPlate() >= MassRequired) {
		OpenDoor();
	}
	else if(IsDoorOpen && GetTotalMassOnPlate() < MassRequired) {
		CloseDoor();
	}

	/*	else if (GetTotalMassOnPlate() < MassRequired) {
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	if (IsDoorOpen && GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay) {
		CloseDoor();
	}*/
}

float UOpenDoor::GetTotalMassOnPlate() {
	float totalMass = 0.0f;
	/*
	TArray<AActor*> actors;
	PressurePlate->GetOverlappingActors(OUT actors);
	*/

	TArray<UPrimitiveComponent*> components;
	PressurePlate->GetOverlappingComponents(OUT components);

	for (UPrimitiveComponent* component : components) {
		UE_LOG(LogTemp, Warning, TEXT("component %f"), component->CalculateMass());
		totalMass += component->GetMass();
	}
	
	UE_LOG(LogTemp, Warning, TEXT("total %f"), totalMass);

	return totalMass;
}

