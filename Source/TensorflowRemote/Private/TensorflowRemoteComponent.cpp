// Fill out your copyright notice in the Description page of Project Settings.


#include "TensorflowRemoteComponent.h"
#include "SocketIOClient.h"
#include "CULambdaRunnable.h"


UTensorflowRemoteComponent::UTensorflowRemoteComponent()
{
	bConnectOnBeginPlay = true;
	ServerType = ETFServerType::SERVER_PYTHON;
	ServerAddressAndPort = TEXT("http://localhost:3000");

	Socket = ISocketIOClientModule::Get().NewValidNativePointer();
}

UTensorflowRemoteComponent::~UTensorflowRemoteComponent()
{
	ISocketIOClientModule::Get().ReleaseNativePointer(Socket);
}

void UTensorflowRemoteComponent::BeginPlay()
{
	Super::BeginPlay();
	
	//Setup callbacks
	Socket->OnConnectedCallback = [this](const FString& InSessionId)
	{
		if (Socket.IsValid())
		{
			bIsConnectedToBackend = true;
		}
	};

	Socket->OnDisconnectedCallback = [this](const ESIOConnectionCloseReason Reason)
	{
		if (Socket.IsValid())
		{
			bIsConnectedToBackend = false;
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

void UTensorflowRemoteComponent::SendJsonInput(const FString& InputData)
{
	UE_LOG(TensorflowBaseLog, Log, TEXT("Not Implemented"));
}

void UTensorflowRemoteComponent::SendJsonInputGraphResult(const FString& InputData, FString& Result, struct FLatentActionInfo LatentInfo)
{
	FCULatentAction* LatentAction = FCULatentAction::CreateLatentAction(LatentInfo, this);
	LatentAction->Call();	//resume the latent action
}
