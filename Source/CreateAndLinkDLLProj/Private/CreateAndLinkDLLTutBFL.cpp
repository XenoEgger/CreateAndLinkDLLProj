// Fill out your copyright notice in the Description page of Project Settings.

#include "CreateAndLinkDLLProj.h"
#include "CreateAndLinkDLLTutBFL.h"

typedef float(*_getCircleArea)(float radius); // Declare the DLL function.

_getCircleArea DLLgetCircleArea;
void *DLLHandle;

bool UCreateAndLinkDLLTutBFL::importDLL(FString folder, FString name)
{
	FString filePath = *FPaths::GamePluginsDir() + folder + name;
	
	if (FPaths::FileExists(filePath))
	{
		DLLHandle = FPlatformProcess::GetDllHandle(*filePath); // Retrieve the DLL.
		if (DLLHandle != NULL)
		{
			return true;
		}
	}
	return false;
}

bool UCreateAndLinkDLLTutBFL::importMethod(FString name)
{
	if (DLLHandle != NULL)
	{
		FString procName = name; // The exact name of the DLL function.
		DLLgetCircleArea = (_getCircleArea)FPlatformProcess::GetDllExport(DLLHandle, *procName); // Export the DLL function.
		if (DLLgetCircleArea != NULL)
		{
			return true;
		}
	}
	return false;
}

float UCreateAndLinkDLLTutBFL::getCircleAreaDLL(float radius)
{
	if (DLLgetCircleArea != NULL)
	{
		float out = DLLgetCircleArea(radius); // Call the DLL function, with arguments corresponding to the signature and return type of the function.
		return out; // return to UE
	}
	return -1.00f;
}

void UCreateAndLinkDLLTutBFL::freeDLL()
{
	if (DLLHandle != NULL)
	{
		FPlatformProcess::FreeDllHandle(DLLHandle);
	}
}


