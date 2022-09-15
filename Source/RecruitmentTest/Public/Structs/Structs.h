// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/StaticMesh.h"
#include "Math/Color.h"
#include "Structs.generated.h"


USTRUCT(BlueprintType)
struct FShapeParameter
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	FName ParamName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	UStaticMesh* StaticMesh;
};


USTRUCT(BlueprintType)
struct FColorParameter
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	FName ParamName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	FLinearColor TargetColor;
};


USTRUCT(BlueprintType)
struct FParametersInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	TMap<FName, int> ParametersMap;
};