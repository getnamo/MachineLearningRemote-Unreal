// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/Engine/Classes/Engine/LatentActionManager.h"
#include "MachineLearningBaseComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMLResultSignature, FString, Result);

/** 
*	Base component for both remote and standard MachineLearning components.
*	Considered abstract, ensures all MachineLearning components have same base API
*/
UCLASS(ClassGroup = Computing)
class MACHINELEARNINGREMOTE_API UMachineLearningBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UMachineLearningBaseComponent();

	/** On bound event received. */
	UPROPERTY(BlueprintAssignable, Category = TensorflowEvents)
	FMLResultSignature OnResult;

	/** What this means is different for each sub-type */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = TensorflowRemoteProperties)
	bool bIsConnectedToBackend;

	/** Send input to ML side result comes back to the OnResult event */
	UFUNCTION(BlueprintCallable, Category = TensorflowFunctions)
	virtual void SendJsonInput(const FString& InputData);

	/** Latent version of SensJsonInput */
	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo"), Category = TensorflowFunctions)
	virtual void SendJsonInputGraphResult(const FString& InputData, FString& Result, struct FLatentActionInfo LatentInfo);

};
