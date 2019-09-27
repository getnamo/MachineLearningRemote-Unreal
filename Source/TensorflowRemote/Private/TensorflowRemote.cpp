// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TensorflowRemote.h"

DEFINE_LOG_CATEGORY(TensorflowBaseLog);

#define LOCTEXT_NAMESPACE "FTensorflowRemoteModule"

void FTensorflowRemoteModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FTensorflowRemoteModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTensorflowRemoteModule, TensorflowRemote)