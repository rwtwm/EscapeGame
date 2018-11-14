// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"



// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

}

//sets rotation of door to be open. Also prints to log.
void UOpenDoor::OpenDoor()
{
	AActor* Owner = GetOwner();
	FString RotatorString = Owner->GetActorRotation().ToString();
	FString OwnerName = Owner->GetName();

	UE_LOG(LogTemp, Warning, TEXT("%s has rotation %s"), *OwnerName, *RotatorString);

	//Only rotating the door around the z-axis
	FRotator NewRotation = FRotator(0.0f, DoorRotation, 0.0f);
	Owner->SetActorRotation(NewRotation);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate && PressurePlate->IsOverlappingActor(PressureTriggerActor))
	{
		OpenDoor();
	}
}

