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
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	ParentPlayerController->GetPlayerViewPoint(PlayerLocation, PlayerRotation);
	
	//Debug printing for location and rotation
	/*LocationReport = PlayerLocation.ToString();
	RotationReport = PlayerRotation.ToString();
	UE_LOG(LogTemp, Warning, TEXT("Player Position: %s.  Player Rotation: %s"), *LocationReport, *RotationReport);*/
	
	ReachEnd = PlayerLocation + PlayerRotation.Vector() * Reach;

	DrawDebugLine(
		GetWorld(),
		PlayerLocation,
		ReachEnd,
		FColor(255, 0, 0)
	); //Function call across multiple lines
	
}

