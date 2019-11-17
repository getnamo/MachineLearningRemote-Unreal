// Fill out your copyright notice in the Description page of Project Settings.


#include "MachineLearningRemoteComponent.h"
#include "MachineLearningBase.h"
#include "SocketIOClient.h"
#include "CULambdaRunnable.h"


UMachineLearningRemoteComponent::UMachineLearningRemoteComponent()
{
	bConnectOnBeginPlay = true;
	ServerType = ETFServerType::SERVER_PYTHON;
	ServerAddressAndPort = TEXT("http://localhost:3000");

	Socket = ISocketIOClientModule::Get().NewValidNativePointer();
}

UMachineLearningRemoteComponent::~UMachineLearningRemoteComponent()
{
	ISocketIOClientModule::Get().ReleaseNativePointer(Socket);
}

void UMachineLearningRemoteComponent::BeginPlay()
{
	Super::BeginPlay();
	
	//Setup callbacks
	Socket->OnConnectedCallback = [this](const FString& InSessionId)
	{
		if (Socket.IsValid())
		{
			bIsConnectedToBackend = true;
			OnConnectedToBackend.Broadcast(InSessionId);
		}
	};

	Socket->OnDisconnectedCallback = [this](const ESIOConnectionCloseReason Reason)
	{
		if (Socket.IsValid())
		{
			bIsConnectedToBackend = false;
			OnDisconnectedFromBackend.Broadcast(Socket->LastSessionId);
		}
	};

	Socket->OnNamespaceConnectedCallback = [this](const FString& Namespace)
	{
		if (Socket.IsValid())
		{
		}
	};

	Socket->OnNamespaceDisconnectedCallback = [this](const FString& Namespace)
	{
		if (Socket.IsValid())
		{

		}
	};
	Socket->OnReconnectionCallback = [this](const uint32 AttemptCount, const uint32 DelayInMs)
	{
		if (Socket.IsValid())
		{
		}
	};

	Socket->OnFailCallback = [this]()
	{
		if (Socket.IsValid())
		{
		};
	};

	if (bConnectOnBeginPlay)
	{
		Socket->Connect(ServerAddressAndPort);
	}
}

void UMachineLearningRemoteComponent::SendInput(const FString& InputData, const FString& FunctionName /*= TEXT("onJsonInput")*/)
{
	UE_LOG(MLBaseLog, Log, TEXT("Emitting test"));

	Socket->Emit(TEXT("test"), TEXT("hello from ue4 remote"), [](auto ResponseArray) 
	{
		//auto Response = ResponseArray[0];

		UE_LOG(MLBaseLog, Log, TEXT("Got callback response: %s"), *USIOJConvert::ToJsonString(ResponseArray));
		
	});
}

void UMachineLearningRemoteComponent::SendInputGraphResult(const FString& InputData, FString& ResultData, struct FLatentActionInfo LatentInfo, const FString& FunctionName /*= TEXT("onJsonInput")*/)
{
	FCULatentAction* LatentAction = FCULatentAction::CreateLatentAction(LatentInfo, this);
	LatentAction->Call();	//resume the latent action
}
