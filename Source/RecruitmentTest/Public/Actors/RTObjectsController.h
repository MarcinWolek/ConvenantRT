// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structs/Structs.h"
#include "RTObjectsController.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(RTObjectControllerLog, Log, All);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FParametersListDelegate, const FParametersInfo&, ParametersList);

class ARTBaseActor;
class IChangeColorComponent;
class IChangeShapeComponent;


UCLASS()
class RECRUITMENTTEST_API ARTObjectsController : public AActor
{
	GENERATED_BODY()
	

public:

	UPROPERTY(BlueprintAssignable, Category="Events")
	FParametersListDelegate OnComponentsRefreshed;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<ARTBaseActor> SpawnObject;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TArray<FShapeParameter> ShapeParametersList;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TArray<FColorParameter> ColorParametersList;

	UPROPERTY(BlueprintReadOnly, Category = "Spawning")
	TArray<ARTBaseActor*> SpawnedObjects;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning|Components")
	class UBoxComponent* SpawningVolume;

private:

	TMap<FName, FShapeParameter> ShapeParametersMap;
	TMap<FName, FColorParameter> ColorParametersMap;

	TMap<FName, TArray<TScriptInterface<IChangeColorComponent>>> ColorComponetsList;
	TMap<FName, TArray<TScriptInterface<IChangeShapeComponent>>> ShapeComponetsList;

public:	
	// Sets default values for this actor's properties
	ARTObjectsController();

	UFUNCTION(BlueprintCallable, Category="RTObjectsController|Funtions")
	void SpawnObjects(const int Amount);

	UFUNCTION(BlueprintCallable, Category = "RTObjectsController|Funtions")
	void DespawnObjects();

	UFUNCTION(BlueprintCallable, Category = "RTObjectsController|Funtions")
	void PerformOnObjectDestroyed(const TScriptInterface<IChangeShapeComponent> ShapeComponentToRemove, const TScriptInterface<IChangeColorComponent> ColorComponentToRemove);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void DistributeShapeParamsOnSpawn(const int Amount);

	UFUNCTION()
	void DistributeColorParamsOnSpawn(const int Amount);

	UFUNCTION()
	void RefreshShapeComponents(const TScriptInterface<IChangeShapeComponent> ComponentToRemove);

	UFUNCTION()
	void RefreshColorComponents(const TScriptInterface<IChangeColorComponent> ComponentToRemove);

	UFUNCTION()
	void SendParametersInfo() const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
