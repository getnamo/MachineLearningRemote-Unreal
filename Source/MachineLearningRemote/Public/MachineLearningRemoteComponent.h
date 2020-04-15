// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MachineLearningBaseComponent.h"
#include "SocketIONative.h"
#include "SIOJsonValue.h"
#include "MachineLearningRemoteComponent.generated.h"

UENUM(BlueprintType)
enum class ETFServerType : uint8
{
	SERVER_PYTHON,
	SERVER_NODEJS
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMLScriptSignature, FString, ScriptName);

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

	UPROPERTY(BlueprintAssignable, Category = MachineLearningEvents)
	FMLScriptSignature OnScriptStarted;

	/** remote server and address, default localhost:3000 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = MLRemoteProperties)
	FString ServerAddressAndPort;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = MLRemoteProperties)
	FString SendInputEventName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = MLRemoteProperties)
	FString StartScriptEventName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = MLRemoteProperties)
	FString ScriptStartedEventName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = MLRemoteProperties)
	FString LogEventName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = MLRemoteProperties)
	bool bConnectOnBeginPlay;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = MLRemoteProperties)
	bool bStartScriptOnConnection;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = MLRemoteProperties)
	bool bScriptRunning;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = MLRemoteProperties)
	FString DefaultScript;

	/** Support both python and nodejs servers */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = MLRemoteProperties)
	ETFServerType ServerType;

	virtual void BeginPlay() override;

	/** For remote ML components we can use socket.io protocol to communicate objects directly. Return result in graph context. */
	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo"), Category = MLFunctions)
	virtual void SendSIOJsonInput(USIOJsonValue* InputData, USIOJsonValue*& ResultData, struct FLatentActionInfo LatentInfo, const FString& FunctionName = TEXT("on_json_input"));

	/** Start designated script. Get's called on beginplay by default*/
	UFUNCTION(BlueprintCallable, Category = MLFunctions)
	virtual void StartScript(const FString& ScriptName);

	//NB by default python pep expects lowercase_lowercase function names. This is different from BaseComponent defaults, which uses camelCase
	virtual void SendStringInput(const FString& InputData, const FString& FunctionName = TEXT("on_json_input")) override;
	virtual void SendStringInput(const FString& InputData, TFunction<void(const FString& ResultData)> ResultCallback, const FString& FunctionName = TEXT("on_json_input")) override;
	virtual void SendRawInput(const TArray<float>& InputData, const FString& FunctionName = TEXT("on_float_array_input")) override;
	virtual void SendRawInput(const TArray<float>& InputData, TFunction<void(TArray<float>& ResultData)> ResultCallback, const FString& FunctionName = TEXT("on_float_array_input")) override;
	virtual void SendStringInputGraphCallback(const FString& InputData, FString& ResultData, struct FLatentActionInfo LatentInfo, const FString& FunctionName = TEXT("on_json_input")) override;
	virtual void SendRawInputGraphCallback(const TArray<float>& InputData, TArray<float>& ResultData, struct FLatentActionInfo LatentInfo, const FString& FunctionName = TEXT("on_float_array_input")) override;

protected:
	TSharedPtr<FSocketIONative> Socket;
};
