// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TensorflowBaseComponent.h"
#include "SocketIONative.h"
#include "TensorflowRemoteComponent.generated.h"

UENUM(BlueprintType)
enum class ETFServerType : uint8
{
	SERVER_PYTHON,
	SERVER_NODEJS
};

/**
 * Implements Tensorflow API via remote server calls
 */
UCLASS(BlueprintType, ClassGroup = Computing, meta = (BlueprintSpawnableComponent))
class TENSORFLOWREMOTE_API UTensorflowRemoteComponent : public UTensorflowBaseComponent
{
	GENERATED_BODY()
public:

	UTensorflowRemoteComponent();

	/** remote server and address, default localhost:3000 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = TensorflowRemoteProperties)
	FString ServerAddressAndPort;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = TensorflowRemoteProperties)
	bool bConnectOnBeginPlay;

	/** Support both python and nodejs servers */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = TensorflowRemoteProperties)
	ETFServerType ServerType;


	virtual void SendJsonInput(const FString& InputData) override;

	virtual void SendJsonInputGraphResult(const FString& InputData, FString& Result, struct FLatentActionInfo LatentInfo);

protected:
	TSharedPtr<FSocketIONative> Socket;
};
