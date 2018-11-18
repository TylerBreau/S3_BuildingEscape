// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
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


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	player = GetOwner();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	FVector viewPointLocation;
	FRotator viewPointRotation;
	player->GetActorEyesViewPoint(OUT viewPointLocation, OUT viewPointRotation);


	FVector lineTraceEnd = viewPointLocation + (viewPointRotation.Vector() * reach);
	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT hit, 
		viewPointLocation, 
		lineTraceEnd, 
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), 
		FCollisionQueryParams(FName(TEXT("")), false, player)
	);
	
	if (hit.GetActor()) {
		UE_LOG(LogTemp, Warning, TEXT("%s"), *hit.GetActor()->GetName());
	}

	//DrawDebugLine(GetWorld(), viewPointLocation, lineTraceEnd, FColor(255, 0, 0), false, 0.0f, 0, 10.0f);

	//GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint();
}

