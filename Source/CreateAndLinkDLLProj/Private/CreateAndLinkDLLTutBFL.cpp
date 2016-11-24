// Fill out your copyright notice in the Description page of Project Settings.

#include "CreateAndLinkDLLProj.h"
#include "CreateAndLinkDLLTutBFL.h"
#include <string>

typedef float(*_getCircleArea)(float radius); // Declare the DLL function.
typedef std::string(*_getCircleString)(std::string baseString); // Declare the DLL function.

_getCircleArea DLLgetCircleArea;
_getCircleString DLLgetCircleString;

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

bool UCreateAndLinkDLLTutBFL::importMethodGetCircleArea()
{
	if (DLLHandle != NULL)
	{
		DLLgetCircleArea = NULL;
		FString procName = "getCircleArea"; // The exact name of the DLL function.
		DLLgetCircleArea = (_getCircleArea)FPlatformProcess::GetDllExport(DLLHandle, *procName); // Export the DLL function.
		if (DLLgetCircleArea != NULL)
		{
			return true;
		}
	}
	return false;
}

bool UCreateAndLinkDLLTutBFL::importMethodGetCircleString()
{
	if (DLLHandle != NULL)
	{
		DLLgetCircleString = NULL;
		FString procName = "getCircleString"; // The exact name of the DLL function.
		DLLgetCircleString = (_getCircleString)FPlatformProcess::GetDllExport(DLLHandle, *procName); // Export the DLL function.
		if (DLLgetCircleString != NULL)
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
		float out = float(DLLgetCircleArea(radius)); // Call the DLL function, with arguments corresponding to the signature and return type of the function.
		return out; // return to UE
	}
	return -1.00f;
}

FString UCreateAndLinkDLLTutBFL::getCircleStringDLL(FString baseString)
{
	if (DLLgetCircleString != NULL)
	{
		std::string baseStringUTF8(TCHAR_TO_UTF8(*baseString));
		std::string resultFromDLLString = std::string(DLLgetCircleString(baseStringUTF8));

		return (resultFromDLLString.c_str());
	}
	return "Error: getCircleStringDLL didn't return!";
}

void UCreateAndLinkDLLTutBFL::freeDLL()
{
	if (DLLHandle != NULL)
	{
		FPlatformProcess::FreeDllHandle(DLLHandle);
	}
}


