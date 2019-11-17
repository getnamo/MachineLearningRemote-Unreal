// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/Engine/Classes/Engine/LatentActionManager.h"
#include "MachineLearningBaseComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMLResultSignature, FString, ResultData, FString, CallingFunctionName);

/** 
*	Base component for both remote and standard MachineLearning components.
*	Considered abstract, ensures all MachineLearning components have same base API
*/
UCLASS(ClassGroup = Computing)
class MACHINELEARNINGBASE_API UMachineLearningBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UMachineLearningBaseComponent();

	/** SendInput variant will return data to this event. */
	UPROPERTY(BlueprintAssignable, Category = TensorflowEvents)
	FMLResultSignature OnInputResult;

	/** What this means is different for each sub-type */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = TensorflowRemoteProperties)
	bool bIsConnectedToBackend;

	/** Send input to ML side result comes back to the OnResult event. Optionally re-target to another function name. */
	UFUNCTION(BlueprintCallable, Category = TensorflowFunctions)
	virtual void SendInput(const FString& InputData, const FString& FunctionName = TEXT("onJsonInput"));

	/** Send input to ML side result will come back as a latent action in the graph. Recommended method. Optionally re-target to another function name. */
	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo"), Category = TensorflowFunctions)
	virtual void SendInputGraphResult(const FString& InputData, FString& ResultData, struct FLatentActionInfo LatentInfo, const FString& FunctionName = TEXT("onJsonInput"));

};
