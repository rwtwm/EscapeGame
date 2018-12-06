// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "engine/World.h"


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
	ParentDoor = GetOwner();
	DefaultDoorRotation = ParentDoor->GetActorRotation();
	PressureTriggerActor = GetWorld()->GetFirstPlayerController()->GetPawn();

}

//sets rotation of door to be open. Also prints to log.
void UOpenDoor::OpenDoor()
{
	//Only rotating the door around the z-axis
	ParentDoor->SetActorRotation(FRotator(0.0f, DoorRotation, 0.0f));
}

void UOpenDoor::CloseDoor()
{
	ParentDoor->SetActorRotation(DefaultDoorRotation);
	LastDoorOpenTime = 0.0f;
}




// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate && GetTotalMassOfActorsOnTrigger() > 40.0f)
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
		
		//UE_LOG(LogTemp, Warning, TEXT("DoorOpened"));
	}

	if (LastDoorOpenTime > 0.0f && GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		CloseDoor();
		//UE_LOG(LogTemp, Warning, TEXT("DoorClosed"));
	}

	if (PressurePlate)
	{
		GetTotalMassOfActorsOnTrigger();
	}

}

float UOpenDoor::GetTotalMassOfActorsOnTrigger()
{
	float TotalMass = 0.0f;

	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OverlappingActors); //OUT parameter

	for (auto OverlappingActor : OverlappingActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor %s on trigger"), *(OverlappingActor->GetName()));
		TotalMass += OverlappingActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	

	UE_LOG(LogTemp, Warning, TEXT("Mass on Trigger is %s"), *(FString::SanitizeFloat(TotalMass)));

	return TotalMass;
}

