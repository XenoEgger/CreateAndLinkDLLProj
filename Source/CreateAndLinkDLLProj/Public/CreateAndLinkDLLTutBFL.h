// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "CreateAndLinkDLLTutBFL.generated.h"

/**
 * 
 */
UCLASS()
class CREATEANDLINKDLLPROJ_API UCreateAndLinkDLLTutBFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "My DLL Library")
	static bool importDLL( FString folder, FString name);

	UFUNCTION(BlueprintCallable, Category = "My DLL Library")
	static bool importMethod( FString name);

	UFUNCTION(BlueprintCallable, Category = "My DLL Library")
	static float getCircleAreaDLL(float radius);
	
	UFUNCTION(BlueprintCallable, Category = "My DLL Library")
	static void freeDLL();
};
