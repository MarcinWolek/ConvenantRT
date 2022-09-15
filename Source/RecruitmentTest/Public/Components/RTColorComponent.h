// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/Interfaces.h"
#include "RTColorComponent.generated.h"


UCLASS(BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RECRUITMENTTEST_API URTColorComponent : public UActorComponent, public IChangeColorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category="Materials Parameters", meta=(tooltip="Name of material color parameter"))
	FName MaterialParameterName;

	UPROPERTY()
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY()
	class UMaterialInstanceDynamic* DynamicMaterial;

	UPROPERTY()
	FName ParameterName;

public:	
	// Sets default values for this component's properties
	URTColorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
public:
	void ApplyParameter_Implementation(const FColorParameter& InParameter) override;

	FName CurrentParameterName_Implementation() override;

	void NativeApplyParameter(const FColorParameter& InParameter) override;

	FName NativeCurrentParameterName() override;

};
