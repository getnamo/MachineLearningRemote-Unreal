// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MachineLearningBaseComponent.h"
#include "SocketIONative.h"
#include "MachineLearningRemoteComponent.generated.h"

UENUM(BlueprintType)
enum class ETFServerType : uint8
{
	SERVER_PYTHON,
	SERVER_NODEJS
};

/**
 * Implements ML API via remote server calls
 */
UCLASS(BlueprintType, ClassGroup = Computing, meta = (BlueprintSpawnableComponent))
class MACHINELEARNINGREMOTE_API UMachineLearningRemoteComponent : public UMachineLearningBaseComponent
{
	GENERATED_BODY()
public:

	UMachineLearningRemoteComponent();
	~UMachineLearningRemoteComponent();

	/** remote server and address, default localhost:3000 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = TensorflowRemoteProperties)
	FString ServerAddressAndPort;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = TensorflowRemoteProperties)
	bool bConnectOnBeginPlay;

	/** Support both python and nodejs servers */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = TensorflowRemoteProperties)
	ETFServerType ServerType;

	virtual void BeginPlay() override;
	virtual void SendInput(const FString& InputData, const FString& FunctionName = TEXT("onJsonInput")) override;
	virtual void SendInputGraphResult(const FString& InputData, FString& ResultData, struct FLatentActionInfo LatentInfo, const FString& FunctionName = TEXT("onJsonInput")) override;

protected:
	TSharedPtr<FSocketIONative> Socket;
};
