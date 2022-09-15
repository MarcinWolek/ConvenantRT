// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/RTBaseActor.h"
#include "Actors/RTObjectsController.h"
#include "Components/Interfaces/Interfaces.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

DEFINE_LOG_CATEGORY(RTObjectControllerLog);


// Sets default values
ARTObjectsController::ARTObjectsController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawningVolume = CreateDefaultSubobject<UBoxComponent>(FName(TEXT("SpawningVolume")));
}

// Called when the game starts or when spawned
void ARTObjectsController::BeginPlay()
{
	Super::BeginPlay();
	
	int ShapeParamsNum = ShapeParametersList.Num();
	ShapeParametersMap.Reserve(ShapeParamsNum);

	for (int i = 0; i < ShapeParamsNum; i++)
	{
		ShapeParametersMap.Add(ShapeParametersList[i].ParamName, ShapeParametersList[i]);
	}

	int ColorParamsNum = ColorParametersList.Num();
	ColorParametersMap.Reserve(ColorParamsNum);

	for (int i = 0; i < ColorParamsNum; i++)
	{
		ColorParametersMap.Add(ColorParametersList[i].ParamName, ColorParametersList[i]);
	}
}

// Called every frame
void ARTObjectsController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARTObjectsController::SpawnObjects(const int Amount)
{
	if (Amount <= 0)
		return;

	if (SpawnedObjects.Num() > 0)
		DespawnObjects();

	SpawnedObjects.Reserve(Amount);

	for (int i = 0; i < Amount; i++)
	{
		//Randomize position
		FVector RandomPosition = UKismetMathLibrary::RandomPointInBoundingBox(SpawningVolume->GetComponentToWorld().GetLocation(), SpawningVolume->GetScaledBoxExtent());

		//Randomize rotation
		float RandomYaw = FMath::RandRange(0.f, 180.0f);
		FRotator RandomRotation = FRotator(0.f, RandomYaw, 0.f);

		//Spawning objects
		ARTBaseActor* SpawnedObject = GetWorld()->SpawnActor<ARTBaseActor>(SpawnObject, RandomPosition, RandomRotation);
		SpawnedObject->OnDestroyComponentsEvent.AddDynamic(this, &ARTObjectsController::PerformOnObjectDestroyed);
		SpawnedObjects.Add(SpawnedObject);

		//Randomizing scale
		float RandomValue = FMath::RandRange(.5f, 1.0f);
		FVector RandomizedScale = FVector(RandomValue, RandomValue, RandomValue);
		SpawnedObject->SetActorScale3D(RandomizedScale);
	}

	DistributeShapeParamsOnSpawn(Amount);
	DistributeColorParamsOnSpawn(Amount);

	SendParametersInfo();

	UE_LOG(RTObjectControllerLog, Log, TEXT(">>>>>> -- RTObjectController: Spawned %d Objects! -- <<<<<<"), SpawnedObjects.Num());
}

void ARTObjectsController::DespawnObjects()
{
	if (SpawnedObjects.Num() == 0)
		return;

	for (int i = 0; i < SpawnedObjects.Num(); i++)
	{
		if(SpawnedObjects[i])
			SpawnedObjects[i]->Destroy();
	}

	SpawnedObjects.Empty();
	ShapeComponetsList.Empty();
	ColorComponetsList.Empty();

	UE_LOG(RTObjectControllerLog, Log, TEXT(">>>>>> -- RTObjectController: Despawned all Objects! -- <<<<<<"));
}

void ARTObjectsController::PerformOnObjectDestroyed(const TScriptInterface<IChangeShapeComponent> ShapeComponentToRemove, const TScriptInterface<IChangeColorComponent> ColorComponentToRemove)
{
	RefreshShapeComponents(ShapeComponentToRemove);
	RefreshColorComponents(ColorComponentToRemove);

	SendParametersInfo();
}

void ARTObjectsController::DistributeShapeParamsOnSpawn(const int Amount)
{
	if (ShapeParametersList.Num() == 0)
		return;

	//Calculation of categories amounts
	int SingleCategoryAmount = Amount / ShapeParametersList.Num();
	int ExcessAmount = Amount % ShapeParametersList.Num();

	TArray<int> CategoriesAmounts;
	TArray<FName> CategoriesNames;
	CategoriesAmounts.Reserve(ShapeParametersList.Num());
	CategoriesNames.Reserve(ShapeParametersList.Num());

	for (int i = 0; i < ShapeParametersList.Num(); i++)
	{
		int Excess = ExcessAmount > 0 ? 1 : 0;
		CategoriesAmounts.Add(SingleCategoryAmount + Excess);
		CategoriesNames.Add(ShapeParametersList[i].ParamName);
		ExcessAmount--;
	}

	//Getting random parameters and applying it to spawned objects
	for (int i = 0; i < SpawnedObjects.Num(); i++)
	{
		TScriptInterface<IChangeShapeComponent> shapeComponent = SpawnedObjects[i]->GetChangeShapeComponent();

		int RandomIndex = CategoriesNames.Num() > 1 ? FMath::RandRange(0, CategoriesNames.Num() - 1) : 0;
		FName RandomParamName = CategoriesNames[RandomIndex];

		shapeComponent->NativeApplyParameter(ShapeParametersMap[RandomParamName]);

		if (!ShapeComponetsList.Contains(RandomParamName))
		{
			TArray<TScriptInterface<IChangeShapeComponent>> ComponentsList;
			ComponentsList.Reserve(CategoriesAmounts[RandomIndex]);
			ShapeComponetsList.Add(RandomParamName, ComponentsList);
		}

		ShapeComponetsList[RandomParamName].Add(shapeComponent);

		CategoriesAmounts[RandomIndex] -= 1;

		if (CategoriesAmounts[RandomIndex] <= 0)
		{
			CategoriesAmounts.RemoveAt(RandomIndex);
			CategoriesNames.RemoveAt(RandomIndex);
		}
	}
}

void ARTObjectsController::DistributeColorParamsOnSpawn(const int Amount)
{
	if (ColorParametersList.Num() == 0)
		return;

	//Calculation of categories amounts
	int SingleCategoryAmount = Amount / ColorParametersList.Num();
	int ExcessAmount = Amount % ColorParametersList.Num();

	TArray<int> CategoriesAmounts;
	TArray<FName> CategoriesNames;
	CategoriesAmounts.Reserve(ColorParametersList.Num());
	CategoriesNames.Reserve(ColorParametersList.Num());

	for (int i = 0; i < ColorParametersList.Num(); i++)
	{
		int Excess = ExcessAmount > 0 ? 1 : 0;
		CategoriesAmounts.Add(SingleCategoryAmount + Excess);
		CategoriesNames.Add(ColorParametersList[i].ParamName);
		ExcessAmount--;
	}

	//Getting random parameters and applying it to spawned objects
	for (int i = 0; i < SpawnedObjects.Num(); i++)
	{
		TScriptInterface<IChangeColorComponent> colorComponent = SpawnedObjects[i]->GetChangeColorComponent();

		int RandomIndex = CategoriesNames.Num() > 1 ? FMath::RandRange(0, CategoriesNames.Num() - 1) : 0;
		FName RandomParamName = CategoriesNames[RandomIndex];

		colorComponent->NativeApplyParameter(ColorParametersMap[RandomParamName]);

		if (!ColorComponetsList.Contains(RandomParamName))
		{
			TArray<TScriptInterface<IChangeColorComponent>> ComponentsList;
			ComponentsList.Reserve(CategoriesAmounts[RandomIndex]);
			ColorComponetsList.Add(RandomParamName, ComponentsList);
		}

		ColorComponetsList[RandomParamName].Add(colorComponent);

		CategoriesAmounts[RandomIndex] -= 1;

		if (CategoriesAmounts[RandomIndex] <= 0)
		{
			CategoriesAmounts.RemoveAt(RandomIndex);
			CategoriesNames.RemoveAt(RandomIndex);
		}
	}
}

void ARTObjectsController::RefreshShapeComponents(const TScriptInterface<IChangeShapeComponent> ComponentToRemove)
{
	FName ChangedParameterName = ComponentToRemove->NativeCurrentParameterName();

	ShapeComponetsList[ChangedParameterName].Remove(ComponentToRemove);

	int ChangedParameterAmount = ShapeComponetsList[ChangedParameterName].Num();

	for (auto& ShapeComponents : ShapeComponetsList)
	{
		//If difference between amount of changed/removed parameters and amount of other parameters is greater than 1,
		//we change one of others parameters to changed/removed parameter
		if (ShapeComponents.Value.Num() - ChangedParameterAmount > 1)
		{
			TScriptInterface<IChangeShapeComponent> ComponentToChange = ShapeComponents.Value[0];
			ComponentToChange->NativeApplyParameter(ShapeParametersMap[ChangedParameterName]);
			ShapeComponetsList[ChangedParameterName].Add(ComponentToChange);
			ShapeComponents.Value.Remove(ComponentToChange);

			if (ShapeComponents.Value.Num() == 0)
			{
				ShapeComponetsList.Remove(ShapeComponents.Key);
			}

			break;
		}
	}
}

void ARTObjectsController::RefreshColorComponents(const TScriptInterface<IChangeColorComponent> ComponentToRemove)
{
	FName ChangedParameterName = ComponentToRemove->NativeCurrentParameterName();

	ColorComponetsList[ChangedParameterName].Remove(ComponentToRemove);

	int ChangedParameterAmount = ColorComponetsList[ChangedParameterName].Num();

	for (auto& ColorComponents : ColorComponetsList)
	{
		//If difference between amount of changed/removed parameters and amount of other parameters is greater than 1,
		//we change one of others parameters to changed/removed parameter
		if (ColorComponents.Value.Num() - ChangedParameterAmount > 1)
		{
			TScriptInterface<IChangeColorComponent> ComponentToChange = ColorComponents.Value[0];
			ComponentToChange->NativeApplyParameter(ColorParametersMap[ChangedParameterName]);
			ColorComponetsList[ChangedParameterName].Add(ComponentToChange);
			ColorComponents.Value.Remove(ComponentToChange);

			if (ColorComponents.Value.Num() == 0)
			{
				ColorComponetsList.Remove(ColorComponents.Key);
			}

			break;
		}
	}
}

void ARTObjectsController::SendParametersInfo() const
{
	FParametersInfo InfoToSend;
	InfoToSend.ParametersMap.Reserve(ShapeComponetsList.Num() + ColorComponetsList.Num());

	for (auto& ShapeComponentSet : ShapeComponetsList)
	{
		InfoToSend.ParametersMap.Add(ShapeComponentSet.Key, ShapeComponentSet.Value.Num());
	}

	for (auto& ColorComponentSet : ColorComponetsList)
	{
		InfoToSend.ParametersMap.Add(ColorComponentSet.Key, ColorComponentSet.Value.Num());
	}

	OnComponentsRefreshed.Broadcast(InfoToSend);
}
