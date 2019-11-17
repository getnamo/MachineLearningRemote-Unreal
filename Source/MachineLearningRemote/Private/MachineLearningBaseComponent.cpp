// Fill out your copyright notice in the Description page of Project Settings.

#include "MachineLearningBaseComponent.h"
#include "MachineLearningRemote.h"
#include "CULambdaRunnable.h"

UMachineLearningBaseComponent::UMachineLearningBaseComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bIsConnectedToBackend = false;
}

void UMachineLearningBaseComponent::SendJsonInput(const FString& InputData)
{
	FString Result = TEXT("not implemented");
	UE_LOG(MLBaseLog, Warning, TEXT("%s"), *Result);
	OnResult.Broadcast(Result);
}

void UMachineLearningBaseComponent::SendJsonInputGraphResult(const FString& InputData, FString& Result, struct FLatentActionInfo LatentInfo)
{
	Result = TEXT("not implemented");

	UE_LOG(MLBaseLog, Warning, TEXT("%s"), *Result);

	FCULatentAction* LatentAction = FCULatentAction::CreateLatentAction(LatentInfo, this);
	LatentAction->Call();	//resume the latent action
}

