// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/Public/DrawDebugHelpers.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	reach = 100.0f;
	// ...
}


FVector UGrabber::GetTargetLocation() {
	FVector viewPointLocation;
	FRotator viewPointRotation;
	player->GetActorEyesViewPoint(OUT viewPointLocation, OUT viewPointRotation);
	return viewPointLocation + (viewPointRotation.Vector() * reach);

}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	player = GetOwner();

	//Get physics handle component
	physicsHandle = player->FindComponentByClass<UPhysicsHandleComponent>();
	if (!physicsHandle) {
		UE_LOG(LogTemp, Error, TEXT("%s missing Physics Handle."), *player->GetName());
	}

	//Get input component
	inputComponent = player->FindComponentByClass<UInputComponent>();
	if (inputComponent) {
		inputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		inputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s missing Input Component."), *player->GetName());
	}
}

void UGrabber::Grab() {
	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT hit,
		player->GetActorLocation(),
		GetTargetLocation(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, player)
	);

	if (hit.GetActor()) {
		physicsHandle->GrabComponent(hit.GetComponent(), NAME_None, hit.GetComponent()->GetOwner()->GetActorLocation(), true);
	}
}

void UGrabber::Release() {
	physicsHandle->ReleaseComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (physicsHandle->GetGrabbedComponent()) {
		physicsHandle->SetTargetLocation(GetTargetLocation());
	}
}

