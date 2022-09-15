// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Structs/Structs.h"
#include "Interfaces.generated.h"


UINTERFACE(MinimalAPI, Blueprintable)
class UChangeShapeComponent : public UInterface
{
	GENERATED_BODY()
};

class IChangeShapeComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ChangeShapeComponent|Interface Functions")
	FName CurrentParameterName();

	UFUNCTION()
	virtual FName NativeCurrentParameterName() = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ChangeShapeComponent|Interface Functions")
	void ApplyParameter(const FShapeParameter& InParameter);

	UFUNCTION()
	virtual void NativeApplyParameter(const FShapeParameter& InParameter) = 0;
};


UINTERFACE(MinimalAPI, Blueprintable)
class UChangeColorComponent : public UInterface
{
	GENERATED_BODY()
};

class IChangeColorComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ChangeColorComponent|Interface Functions")
	FName CurrentParameterName();

	UFUNCTION()
	virtual FName NativeCurrentParameterName() = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ChangeColorComponent|Interface Functions")
	void ApplyParameter(const FColorParameter& InParameter);

	UFUNCTION()
	virtual void NativeApplyParameter(const FColorParameter& InParameter) = 0;
};