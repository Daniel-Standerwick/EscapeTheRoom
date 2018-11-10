// Copyright Daniel Standerwick 2018

#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "WorldCollision.h"


#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsComponent();
	SetupInputComponent();

}

void UGrabber::FindPhysicsComponent()
{
	OwnerController = GetWorld()->GetFirstPlayerController();
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The PhysicsHandle Component Was Not Found On %s Please Add It Through \"Add Component\" To %s"), *GetOwner()->GetName(), *GetOwner()->GetName());
	}
}

void UGrabber::SetupInputComponent()
{
	PawnInput = GetOwner()->FindComponentByClass<UInputComponent>();
	if (PawnInput)
	{
		PawnInput->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		PawnInput->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("The PawnInputComponent Was Not Found On %s Please Add It Through \"Add Component\" To %s"), *GetOwner()->GetName(), *GetOwner()->GetName());
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber Clicked"));

	///Try and reach any actors with physics body collision channel set
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	AActor* ActorHit = HitResult.GetActor();

	/// If we hit something then attach a physics handle
	if (ActorHit)
	{
		PhysicsHandle->GrabComponentAtLocationWithRotation(ComponentToGrab, NAME_None, ActorHit->GetActorLocation(), FRotator(0.f, 0.f, 0.f));
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber Released"));
	///release physics component
	PhysicsHandle->ReleaseComponent();

}

FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	/// Setup Query
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	///Line trace (Ray-Cast) out to reach distance
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	///see what we hit
	AActor* ActorHit = HitResult.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(ActorHit->GetName()));
	}


	return HitResult;
}

FVector UGrabber::GetReachLineStart()
{
	///Get Player viewpoint 
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	FVector LineTraceDirection = PlayerViewPointRotation.Vector();
	return PlayerViewPointLocation;
}

FVector UGrabber::GetReachLineEnd()
{
	///Get Player viewpoint 
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	FVector LineTraceDirection = PlayerViewPointRotation.Vector();
	return PlayerViewPointLocation + LineTraceDirection * Reach;
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	///uncomment to draw a red tracer from player pawn in the world
		//DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(255, 0, 0), false, 0.f, 0.f, 10.f);

	///Line-Trace to see if we can grab anything
	//if the physics handle is attached 
	if (PhysicsHandle->GrabbedComponent)
	{
		//move the object that were holding
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}
}
