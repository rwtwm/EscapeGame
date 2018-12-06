// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Engine/EngineTypes.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	ParentPlayerController = GetWorld()->GetFirstPlayerController();
	
	//Initialises pointers for PhysicsHandler and InputCOmponent
	FindPhysicsHandle();
	FindInputComponent();

}


void UGrabber::FindPhysicsHandle()
{
	///find attached physics handle
	PhysicsHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	//Log Error if physics handle not attached to parent component.
	if (!PhysicsHandler)
	{
		UE_LOG(LogTemp, Error, TEXT("Physics Handler not found for %s"), *(GetOwner()->GetName()));
	}
}

//Identifies the input component attached to the player pawn and binds the input actions to funtions. 
void UGrabber::FindInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent) 
	{
		UE_LOG(LogTemp, Warning, TEXT("InputComponent present on %s"), *(GetOwner()->GetName()));
		InputComponent->BindAction(FName("Grab"), IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction(FName("Grab"), IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InputComponent not found for %s"), *(GetOwner()->GetName()));
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));
	
	//Grab component on physics body
	FHitResult GrabHitResult = RunLineTraceForPhysicsBody();
	
	if (GrabHitResult.GetActor())
	{
		UPrimitiveComponent* ComponentToGrab = GrabHitResult.GetComponent();
				
		PhysicsHandler->GrabComponentAtLocationWithRotation(
			ComponentToGrab,
			NAME_None,
			GrabHitResult.GetActor()->GetActorLocation(),
			GrabHitResult.GetActor()->GetActorRotation()
		);
		
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab released"));
	PhysicsHandler->ReleaseComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(PhysicsHandler->GrabbedComponent)
	{
		PhysicsHandler->SetTargetLocation(GetReachEnd());
	}
}


FHitResult UGrabber::RunLineTraceForPhysicsBody()
{
	FHitResult LineTraceResult = FHitResult();
	FString HitActorName = "";

	//Find the first physics body between 'player location' and reach end
	GetWorld()->LineTraceSingleByObjectType(
		LineTraceResult, //OUT parameter
		PlayerLocation,
		GetReachEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(), false, GetOwner())
	);

	if (LineTraceResult.GetActor()) {
		HitActorName = LineTraceResult.GetActor()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("LineTrace hit: %s"), *HitActorName);
	}

	return LineTraceResult;
}

//Returns the end postion of the grabber 'arms' 
FVector UGrabber::GetReachEnd()
{
	//Player location and player rotation are modified by passing them into this function.
	ParentPlayerController->GetPlayerViewPoint(PlayerLocation, PlayerRotation);
	
	return PlayerLocation + PlayerRotation.Vector() * Reach;
}



