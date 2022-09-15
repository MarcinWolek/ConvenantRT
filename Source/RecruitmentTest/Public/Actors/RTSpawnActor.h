// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actors/RTBaseActor.h"
#include "RTSpawnActor.generated.h"

UCLASS()
class RECRUITMENTTEST_API ARTSpawnActor : public ARTBaseActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Variables|Components")
	class URTColorComponent* ColorComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Variables|Components")
	class URTShapeComponent* ShapeComponent;

public:	
	// Sets default values for this actor's properties
	ARTSpawnActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
