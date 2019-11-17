// Fill out your copyright notice in the Description page of Project Settings.

#include "MachineLearningBaseComponent.h"
#include "MachineLearningBase.h"
#include "Engine/Engine.h"
#include "Runtime/Engine/Public/LatentActions.h"

UMachineLearningBaseComponent::UMachineLearningBaseComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bIsConnectedToBackend = false;
}

void UMachineLearningBaseComponent::SendInput(const FString& InputData, const FString& FunctionName /*= TEXT("Default")*/)
{
	FString ResultData = TEXT("not implemented");
	UE_LOG(MLBaseLog, Warning, TEXT("%s"), *ResultData);
	OnInputResult.Broadcast(ResultData, FunctionName);
}

void UMachineLearningBaseComponent::SendInputGraphResult(const FString& InputData, FString& ResultData, struct FLatentActionInfo LatentInfo, const FString& FunctionName /*= TEXT("Default")*/)
{
	ResultData = TEXT("not implemented");

	UE_LOG(MLBaseLog, Warning, TEXT("%s"), *ResultData);

	//Create a dummy pending latent action that returns in next tick
	UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull);
	if (!World)
	{
		return;
	}

	FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
	FPendingLatentAction *LatentAction = LatentActionManager.FindExistingAction<FPendingLatentAction>(LatentInfo.CallbackTarget, LatentInfo.UUID);
	LatentAction = new FPendingLatentAction();	//safe to use new since latentactionmanager will delete it
	int32 UUID = LatentInfo.UUID;
	LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, LatentAction);
}


