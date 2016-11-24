
#include "CreateAndLinkDLLProj.h"
#include "CreateAndLinkDLLTutBFL.h"
#include <string>

typedef float(*_getCircleArea)(float radius); // Declare a method to store the DLL method getCircleArea.
typedef std::string(*_getAdditionalString)(std::string baseString); // Declare a method to store the DLL method getAdditionalString.

_getCircleArea m_getCircleAreaFromDll;
_getAdditionalString m_getAdditionalStringFromDll;

void *v_dllHandle;

// Method to import a DLL.
bool UCreateAndLinkDLLTutBFL::importDLL(FString folder, FString name)
{
	FString filePath = *FPaths::GamePluginsDir() + folder + "/" + name;
	
	if (FPaths::FileExists(filePath))
	{
		v_dllHandle = FPlatformProcess::GetDllHandle(*filePath); // Retrieve the DLL.
		if (v_dllHandle != NULL)
		{
			return true;
		}
	}
	return false;	// Return an error.
}

// Method to import the method getCircleArea from the DLL.
bool UCreateAndLinkDLLTutBFL::importMethodGetCircleArea()
{
	if (v_dllHandle != NULL)
	{
		m_getCircleAreaFromDll = NULL;
		FString procName = "getCircleArea";	// Needs to be the exact name of the DLL method.
		m_getCircleAreaFromDll = (_getCircleArea)FPlatformProcess::GetDllExport(v_dllHandle, *procName);
		if (m_getCircleAreaFromDll != NULL)
		{
			return true;
		}
	}
	return false;	// Return an error.
}

// Method to import the method getAdditionalString from the DLL.
bool UCreateAndLinkDLLTutBFL::importMethodGetAdditionalString()
{
	if (v_dllHandle != NULL)
	{
		m_getAdditionalStringFromDll = NULL;
		FString procName = "getAdditionalString"; // Needs to be the exact name of the DLL method.
		m_getAdditionalStringFromDll = (_getAdditionalString)FPlatformProcess::GetDllExport(v_dllHandle, *procName);
		if (m_getAdditionalStringFromDll != NULL)
		{
			return true;
		}
	}
	return false;	// Return an error.
}

// Method to call the method m_getCircleAreaFromDll that was imported from the DLL.
float UCreateAndLinkDLLTutBFL::getCircleAreaFromDll(float radius)
{
	if (m_getCircleAreaFromDll != NULL)
	{
		float out = float(m_getCircleAreaFromDll(radius)); // Call the DLL method with arguments corresponding to the exact signature and return type of the method.
		return out;
	}
	return -1.00f;	// Return an error.
}

// Method to call the method m_getAdditionalStringFromDll that was imported from the DLL.
FString UCreateAndLinkDLLTutBFL::getAdditionalStringFromDll(FString baseString)
{
	if (m_getAdditionalStringFromDll != NULL)
	{
		std::string baseStringUTF8(TCHAR_TO_UTF8(*baseString));
		std::string resultFromDLLString = std::string(m_getAdditionalStringFromDll(baseStringUTF8));

		return (resultFromDLLString.c_str());
	}
	return "Error: Method was probabey not imported yet!";	// Return an error.
}

// If you love something  set it free.
void UCreateAndLinkDLLTutBFL::freeDLL()
{
	if (v_dllHandle != NULL)
	{
		FPlatformProcess::FreeDllHandle(v_dllHandle);
	}
}


