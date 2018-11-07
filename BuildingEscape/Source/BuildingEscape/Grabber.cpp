// Copyright Daniel Standerwick 2018

#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	OwnerController = GetWorld()->GetFirstPlayerController();
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Get Player viewpoint 
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	OwnerController->GetPlayerViewPoint(OUT PlayerViewPointLocation,OUT PlayerViewPointRotation);
	UE_LOG(LogTemp, Warning, TEXT("Location: %s | Rotation: %s"), *PlayerViewPointLocation.ToString() , *PlayerViewPointRotation.ToString());

	//Ray-Cast out to reach distance

	//see what we hit


}
