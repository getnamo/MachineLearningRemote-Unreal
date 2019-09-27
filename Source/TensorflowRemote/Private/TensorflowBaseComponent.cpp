// Fill out your copyright notice in the Description page of Project Settings.

#include "TensorflowBaseComponent.h"
#include "TensorflowRemote.h"
#include "CULambdaRunnable.h"
#include "Engine/Engine.h"

UTensorflowBaseComponent::UTensorflowBaseComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTensorflowBaseComponent::SendJsonInput(const FString& InputData)
{
	UE_LOG(TensorflowBaseLog, Warning, TEXT("not implemented"));
}

void UTensorflowBaseComponent::SendJsonInputGraphResult(const FString& InputData, FLatentActionInfo LatentInfo)
{
	UE_LOG(TensorflowBaseLog, Warning, TEXT("not implemented"));

	//resolve the latent action
	UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull);
	FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
	int32 UUID = LatentInfo.UUID;
	FCUPendingLatentAction *LatentAction = LatentActionManager.FindExistingAction<FCUPendingLatentAction>(LatentInfo.CallbackTarget, UUID);
	LatentAction = new FCUPendingLatentAction(LatentInfo);
	LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, LatentAction);
	LatentAction->Call();	//resume the latent action
}

