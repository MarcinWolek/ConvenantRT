// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RTShapeComponent.h"

// Sets default values for this component's properties
URTShapeComponent::URTShapeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void URTShapeComponent::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent = Cast<UStaticMeshComponent>(GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass()));	
}


// Called every frame
void URTShapeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void URTShapeComponent::NativeApplyParameter(const FShapeParameter& InParameter)
{
	MeshComponent->SetStaticMesh(InParameter.StaticMesh);
	ParameterName = InParameter.ParamName;
}

FName URTShapeComponent::NativeCurrentParameterName()
{
	return ParameterName;
}

void URTShapeComponent::ApplyParameter_Implementation(const FShapeParameter& InParameter)
{
	NativeApplyParameter(InParameter);
}

FName URTShapeComponent::CurrentParameterName_Implementation()
{
	return ParameterName;
}

