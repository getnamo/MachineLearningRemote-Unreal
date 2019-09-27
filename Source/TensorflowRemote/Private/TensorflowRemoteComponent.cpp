// Fill out your copyright notice in the Description page of Project Settings.


#include "TensorflowRemoteComponent.h"

UTensorflowRemoteComponent::UTensorflowRemoteComponent()
{
	bConnectOnBeginPlay = true;
	ServerType = ETFServerType::SERVER_PYTHON;
	ServerAddressAndPort = TEXT("http://localhost:3000");
}
