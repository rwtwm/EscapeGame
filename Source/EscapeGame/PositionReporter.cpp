// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionReporter.h"


// Sets default values for this component's properties
UPositionReporter::UPositionReporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReporter::BeginPlay()
{
	Super::BeginPlay();
	
	//GetOwner returns a pointer to the owner object. The -> Enables access of methods and variables via pointers. 
	FString ObjectName = GetOwner() -> GetName();
	FString ObjectPos = GetOwner()->GetActorLocation().ToString();
		//"X = xxx, Y = yyy, Z = zzz";

	//UE_LOG requires FString to be 'dereferenced' to be used for string format
	UE_LOG(LogTemp, Warning, TEXT("%s is located at %s"), *ObjectName, *ObjectPos);
	
}


// Called every frame
void UPositionReporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

