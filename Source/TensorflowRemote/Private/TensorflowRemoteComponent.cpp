// Fill out your copyright notice in the Description page of Project Settings.


#include "TensorflowRemoteComponent.h"
#include "CULambdaRunnable.h"


UTensorflowRemoteComponent::UTensorflowRemoteComponent()
{
	bConnectOnBeginPlay = true;
	ServerType = ETFServerType::SERVER_PYTHON;
	ServerAddressAndPort = TEXT("http://localhost:3000");
}

void UTensorflowRemoteComponent::SendJsonInput(const FString& InputData)
{
	UE_LOG(TensorflowBaseLog, Log, TEXT("Not Implemented"));
}

void UTensorflowRemoteComponent::SendJsonInputGraphResult(const FString& InputData, FString& Result, struct FLatentActionInfo LatentInfo)
{
	FCULatentAction* LatentAction = FCULatentAction::CreateLatentAction(LatentInfo, this);
	LatentAction->Call();	//resume the latent action
}
