// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RTColorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values for this component's properties
URTColorComponent::URTColorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;	
}


// Called when the game starts
void URTColorComponent::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent = Cast<UStaticMeshComponent>(GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass()));

	if (MeshComponent)
	{
		DynamicMaterial = UMaterialInstanceDynamic::Create(MeshComponent->GetMaterial(0), this);
		MeshComponent->SetMaterial(0, DynamicMaterial);
	}
}

// Called every frame
void URTColorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void URTColorComponent::NativeApplyParameter(const FColorParameter& InParameter)
{
	ParameterName = InParameter.ParamName;
	DynamicMaterial->SetVectorParameterValue(MaterialParameterName, InParameter.TargetColor);
}

FName URTColorComponent::NativeCurrentParameterName()
{
	return ParameterName;
}

FName URTColorComponent::CurrentParameterName_Implementation()
{
	return ParameterName;
}

void URTColorComponent::ApplyParameter_Implementation(const FColorParameter& InParameter)
{
	NativeApplyParameter(InParameter);
}