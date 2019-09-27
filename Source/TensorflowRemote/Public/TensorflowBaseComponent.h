// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/Engine/Classes/Engine/LatentActionManager.h"
#include "TensorflowBaseComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTFResultSignature, FString, Result);

/** 
*	Base component for both remote and standard Tensorflow component.
*	Considered abstract, ensures all Tensorflow components have same base API
*/
UCLASS(ClassGroup = Computing)
class TENSORFLOWREMOTE_API UTensorflowBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UTensorflowBaseComponent();

	/** On bound event received. */
	UPROPERTY(BlueprintAssignable, Category = TensorflowEvents)
	FTFResultSignature OnResult;

	/** What this means is different for each sub-type */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = TensorflowRemoteProperties)
	bool bIsConnectedToBackend;

	/** Send input to tensorflow side result comes back to the OnResult event */
	UFUNCTION(BlueprintCallable, Category = TensorflowFunctions)
	virtual void SendJsonInput(const FString& InputData);

	/** Latent version of SensJsonInput */
	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo"), Category = TensorflowFunctions)
	virtual void SendJsonInputGraphResult(const FString& InputData, FString& Result, struct FLatentActionInfo LatentInfo);


};
