// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/Interfaces.h"
#include "RTShapeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RECRUITMENTTEST_API URTShapeComponent : public UActorComponent, public IChangeShapeComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY()
	FName ParameterName;

public:	
	// Sets default values for this component's properties
	URTShapeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
public:
	FName CurrentParameterName_Implementation() override;

	void ApplyParameter_Implementation(const FShapeParameter& InParameter) override;

	void NativeApplyParameter(const FShapeParameter& InParameter) override;

	FName NativeCurrentParameterName() override;

};
