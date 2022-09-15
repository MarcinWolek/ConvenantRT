// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/RTSpawnActor.h"
#include "Components/RTColorComponent.h"
#include "Components/RTShapeComponent.h"
#include "Components/Interfaces/Interfaces.h"

// Sets default values
ARTSpawnActor::ARTSpawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ColorComponent = CreateDefaultSubobject<URTColorComponent>(FName(TEXT("ColorComponent")));
	ShapeComponent = CreateDefaultSubobject<URTShapeComponent>(FName(TEXT("ShapeComponent")));

	SetChangeColorComponent(ColorComponent);
	SetChangeShapeComponent(ShapeComponent);
}

// Called when the game starts or when spawned
void ARTSpawnActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARTSpawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

