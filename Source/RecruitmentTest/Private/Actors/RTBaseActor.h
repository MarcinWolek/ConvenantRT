// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/Interfaces/Interfaces.h"
#include "RTBaseActor.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FComponentsDelegate, const TScriptInterface<IChangeShapeComponent>, ShapeComponentInstance, const TScriptInterface<IChangeColorComponent>, ColorComponentInstance);


UCLASS(abstract)
class ARTBaseActor : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintAssignable, Category="Events")
	FComponentsDelegate OnDestroyComponentsEvent;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Variables|Components")
	class UStaticMeshComponent* MainMeshComponent;

	UPROPERTY()
	TScriptInterface<IChangeColorComponent> ChangeColorComponent;

	UPROPERTY()
	TScriptInterface<IChangeShapeComponent> ChangeShapeComponent;

public:	
	// Sets default values for this actor's properties
	ARTBaseActor();

	UFUNCTION(BlueprintCallable, Category = "Variables|Interfaces")
	virtual TScriptInterface<IChangeColorComponent> GetChangeColorComponent() const
	{
		return ChangeColorComponent;
	}

	UFUNCTION(BlueprintCallable, Category = "Variables|Interfaces")
	virtual void SetChangeColorComponent(const TScriptInterface<IChangeColorComponent>& ComponentHolder)
	{
		ChangeColorComponent = ComponentHolder;
	}

	UFUNCTION(BlueprintCallable, Category = "Variables|Interfaces")
	virtual TScriptInterface<IChangeShapeComponent> GetChangeShapeComponent() const
	{
		return ChangeShapeComponent;
	}

	UFUNCTION(BlueprintCallable, Category = "Variables|Interfaces")
	virtual void SetChangeShapeComponent(const TScriptInterface<IChangeShapeComponent>& ComponentHolder)
	{
		ChangeShapeComponent = ComponentHolder;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Destroyed() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
