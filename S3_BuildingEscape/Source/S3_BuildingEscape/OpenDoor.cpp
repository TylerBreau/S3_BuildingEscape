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
	MassRequired = 50.0f;
	PressurePlate = nullptr;
	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("%s missing Pressure Plate."), *GetOwner()->GetName());
	}

	// ...
	Owner = GetOwner();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (!IsDoorOpen && GetTotalMassOnPlate() >= MassRequired) {
		IsDoorOpen = true;
		OnOpen.Broadcast();
	}
	else if(IsDoorOpen && GetTotalMassOnPlate() < MassRequired) {
		IsDoorOpen = false;
		OnClose.Broadcast();
	}
}

float UOpenDoor::GetTotalMassOnPlate() {
	float totalMass = 0.0f;

	if (PressurePlate) {
		TArray<UPrimitiveComponent*> components;
		PressurePlate->GetOverlappingComponents(OUT components);

		for (UPrimitiveComponent* component : components) {
			totalMass += component->CalculateMass();
		}
	}

	return totalMass;
}

