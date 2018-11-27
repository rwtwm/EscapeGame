// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

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
	ParentPlayerController = GetWorld()->GetFirstPlayerController();
	// ...

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty"));

	///find attached physics handle
	PhysicsHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	//Log Error if physics handle not attached to parent component.
	if (PhysicsHandler)
	{
		//Physics Handler is found
	} 
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Physics Handler not found for %s"), *(GetOwner()->GetName()));
	}

}



// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	ParentPlayerController->GetPlayerViewPoint(PlayerLocation, PlayerRotation);
	
	ReachEnd = PlayerLocation + PlayerRotation.Vector() * Reach;

	DrawDebugLine(
		GetWorld(),
		PlayerLocation,
		ReachEnd,
		FColor(255, 0, 0)
	); //Function call across multiple lines


	FHitResult LineTraceResult = FHitResult();
	FString HitActorName = "";

	GetWorld()->LineTraceSingleByObjectType(
		LineTraceResult,
		PlayerLocation,
		ReachEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(), false, GetOwner())
	);

	if (LineTraceResult.GetActor()) {
		HitActorName = LineTraceResult.GetActor()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("LineTrace hit: %s"), *HitActorName);
	}

	

	
}

