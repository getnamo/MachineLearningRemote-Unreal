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
	SendInputEvent = TEXT("sendInput");

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
	//Embed data in a ustruct, this will get auto-serialized into a python/json object on other side
	FMLSendStringObject SendObject;
	SendObject.InputData = InputData;
	SendObject.TargetFunction = FunctionName;

	Socket->Emit(SendInputEvent, FMLSendStringObject::StaticStruct(), &SendObject, [this, FunctionName](auto ResponseArray)
	{
		//UE_LOG(MLBaseLog, Log, TEXT("Got callback response: %s"), *USIOJConvert::ToJsonString(ResponseArray));
		if (ResponseArray.Num() == 0)
		{
			return;
		}
		
		//We only handle the one response for now
		TSharedPtr<FJsonValue> Response = ResponseArray[0];

		//Grab the value as a string
		//Todo: support non-string encoding?
		FString Result;

		if (Response->Type == EJson::String)
		{
			Result = Response->AsString();
		}
		else
		{
			Result = USIOJConvert::ToJsonString(Response);
		}

		OnInputResult.Broadcast(Result, FunctionName);		
	});
}

void UMachineLearningRemoteComponent::SendRawInput(const TArray<float>& InputData, const FString& FunctionName /*= TEXT("onFloatArrayInput")*/)
{
	FCULatentAction* LatentAction = FCULatentAction::CreateLatentAction(LatentInfo, this);

	//Embed data in a ustruct, this will get auto-serialized into a python/json object on other side
	FMLSendRawObject SendObject;
	SendObject.InputData = InputData;
	SendObject.TargetFunction = FunctionName;

	Socket->Emit(SendInputEvent, FMLSendRawObject::StaticStruct(), &SendObject, [this, FunctionName, LatentAction, &ResultData](auto ResponseArray)
	{
		//UE_LOG(MLBaseLog, Log, TEXT("Got callback response: %s"), *USIOJConvert::ToJsonString(ResponseArray));
		if (ResponseArray.Num() == 0)
		{
			return;
		}

		//We only handle the one response for now
		TSharedPtr<FJsonValue> Response = ResponseArray[0];

		if (Response->Type != EJson::Object)
		{
			UE_LOG(MLBaseLog, Warning, TEXT("SendRawInputGraphCallback: Expected float array wrapped object, got %s"), *USIOJConvert::ToJsonString(ResponseArray));
			return;
		}

		FMLSendRawObject ReceiveObject;
		USIOJConvert::JsonObjectToUStruct(Response->AsObject(), FMLSendRawObject::StaticStruct(), &ReceiveObject);

		OnRawInputResult.Broadcast(ReceiveObject.InputData, ReceiveObject.TargetFunction);
	});
}

void UMachineLearningRemoteComponent::SendInputGraphCallback(const FString& InputData, FString& ResultData, struct FLatentActionInfo LatentInfo, const FString& FunctionName /*= TEXT("onJsonInput")*/)
{
	FCULatentAction* LatentAction = FCULatentAction::CreateLatentAction(LatentInfo, this);

	//Embed data in a ustruct, this will get auto-serialized into a python/json object on other side
	FMLSendStringObject SendObject;
	SendObject.InputData = InputData;
	SendObject.TargetFunction = FunctionName;

	Socket->Emit(SendInputEvent, FMLSendStringObject::StaticStruct(), &SendObject, [this, FunctionName, LatentAction, &ResultData](auto ResponseArray)
	{
		//UE_LOG(MLBaseLog, Log, TEXT("Got callback response: %s"), *USIOJConvert::ToJsonString(ResponseArray));
		if (ResponseArray.Num() == 0)
		{
			return;
		}

		//We only handle the one response for now
		TSharedPtr<FJsonValue> Response = ResponseArray[0];

		//Grab the value as a string
		//Todo: support non-string encoding?
		if (Response->Type == EJson::String)
		{
			ResultData = Response->AsString();
		}
		else
		{
			ResultData = USIOJConvert::ToJsonString(Response);
		}

		LatentAction->Call();	//resume the latent action
	});
}

void UMachineLearningRemoteComponent::SendRawInputGraphCallback(const TArray<float>& InputData, TArray<float>& ResultData, struct FLatentActionInfo LatentInfo, const FString& FunctionName /*= TEXT("onJsonInput")*/)
{
	FCULatentAction* LatentAction = FCULatentAction::CreateLatentAction(LatentInfo, this);

	//Embed data in a ustruct, this will get auto-serialized into a python/json object on other side
	FMLSendRawObject SendObject;
	SendObject.InputData = InputData;
	SendObject.TargetFunction = FunctionName;

	Socket->Emit(SendInputEvent, FMLSendRawObject::StaticStruct(), &SendObject, [this, FunctionName, LatentAction, &ResultData](auto ResponseArray)
	{
		//UE_LOG(MLBaseLog, Log, TEXT("Got callback response: %s"), *USIOJConvert::ToJsonString(ResponseArray));
		if (ResponseArray.Num() == 0)
		{
			return;
		}

		//We only handle the one response for now
		TSharedPtr<FJsonValue> Response = ResponseArray[0];

		if (Response->Type != EJson::Object)
		{
			UE_LOG(MLBaseLog, Warning, TEXT("SendRawInputGraphCallback: Expected float array wrapped object, got %s"), *USIOJConvert::ToJsonString(ResponseArray));
			return;
		}

		FMLSendRawObject ReceiveObject;
		USIOJConvert::JsonObjectToUStruct(Response->AsObject(), FMLSendRawObject::StaticStruct(), &ReceiveObject);

		ResultData = ReceiveObject.InputData;

		LatentAction->Call();	//resume the latent action
	});
}
