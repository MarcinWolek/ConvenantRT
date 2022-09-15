// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/RTBaseActor.h"


// Sets default values
ARTBaseActor::ARTBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MainMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("MainMesh")));
	SetRootComponent(MainMeshComponent);
}

// Called when the game starts or when spawned
void ARTBaseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARTBaseActor::Destroyed()
{
	OnDestroyComponentsEvent.Broadcast(ChangeShapeComponent, ChangeColorComponent);

	Super::Destroyed();
}

// Called every frame
void ARTBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

