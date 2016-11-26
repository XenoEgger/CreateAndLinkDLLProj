
#include "CreateAndLinkDLLProj.h"
#include "CreateAndLinkDLLTutBFL.h"
#include <string>


typedef bool(*_getInvertedBool)(bool boolState); // Declare a method to store the DLL method getInvertedBool.
typedef int(*_getIntPlusPlus)(int lastInt); // Declare a method to store the DLL method getIntPlusPlus.
typedef float(*_getCircleArea)(float radius); // Declare a method to store the DLL method getCircleArea.
typedef std::string(*_getAdditionalString)(std::string baseString); // Declare a method to store the DLL method getAdditionalString.

_getInvertedBool m_getInvertedBoolFromDll;
_getIntPlusPlus m_getIntPlusPlusFromDll;
_getCircleArea m_getCircleAreaFromDll;
_getAdditionalString m_getAdditionalStringFromDll;

void *v_dllHandle;


#pragma region Load DLL

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
#pragma endregion Load DLL

#pragma region Import Methods

// Imports the method getInvertedBool from the DLL.
bool UCreateAndLinkDLLTutBFL::importMethodGetInvertedBool()
{
	if (v_dllHandle != NULL)
	{
		m_getInvertedBoolFromDll = NULL;
		FString procName = "getInvertedBool";	// Needs to be the exact name of the DLL method.
		m_getInvertedBoolFromDll = (_getInvertedBool)FPlatformProcess::GetDllExport(v_dllHandle, *procName);
		if (m_getInvertedBoolFromDll != NULL)
		{
			return true;
		}
	}
	return false;	// Return an error.
}

// Imports the method getIntPlusPlus from the DLL.
bool UCreateAndLinkDLLTutBFL::importMethodGetIntPlusPlus()
{
	if (v_dllHandle != NULL)
	{
		m_getIntPlusPlusFromDll = NULL;
		FString procName = "getIntPlusPlus";	// Needs to be the exact name of the DLL method.
		m_getIntPlusPlusFromDll = (_getIntPlusPlus)FPlatformProcess::GetDllExport(v_dllHandle, *procName);
		if (m_getIntPlusPlusFromDll != NULL)
		{
			return true;
		}
	}
	return false;	// Return an error.
}

// Imports the method getCircleArea from the DLL.
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

// Imports the method getAdditionalString from the DLL.
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
#pragma endregion Import Methods

#pragma region Method Calls

// Calls the method getInvertedBoolFromDll that was imported from the DLL.
bool UCreateAndLinkDLLTutBFL::getInvertedBoolFromDll(bool boolState)
{
	if (m_getInvertedBoolFromDll != NULL)
	{
		bool out = bool(m_getInvertedBoolFromDll(boolState)); // Call the DLL method with arguments corresponding to the exact signature and return type of the method.
		return out;
	}
	return boolState;	// Return an error.
}

// Calls the method m_getIntPlusPlusFromDll that was imported from the DLL.
int UCreateAndLinkDLLTutBFL::getIntPlusPlusFromDll(int lastInt)
{
	if (m_getIntPlusPlusFromDll != NULL)
	{
		int out = int(m_getIntPlusPlusFromDll(lastInt)); // Call the DLL method with arguments corresponding to the exact signature and return type of the method.
		return out;
	}
	return lastInt;	// Return an error.
}

// Calls the method m_getCircleAreaFromDll that was imported from the DLL.
float UCreateAndLinkDLLTutBFL::getCircleAreaFromDll(float radius)
{
	if (m_getCircleAreaFromDll != NULL)
	{
		float out = float(m_getCircleAreaFromDll(radius)); // Call the DLL method with arguments corresponding to the exact signature and return type of the method.
		return out;
	}
	return -1.00f;	// Return an error.
}

// BUGGY: Calls the method m_getAdditionalStringFromDll that was imported from the DLL.
// To send and receive the origial baseString variable value seems to work all the time. Changes of the return value in the DLL causes the random crashes.
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
#pragma endregion Method Calls

#pragma region Unload DLL

// If you love something  set it free.
void UCreateAndLinkDLLTutBFL::freeDLL()
{
	if (v_dllHandle != NULL)
	{
		m_getInvertedBoolFromDll = NULL;
		m_getIntPlusPlusFromDll = NULL;
		m_getCircleAreaFromDll = NULL;
		m_getAdditionalStringFromDll = NULL;

		FPlatformProcess::FreeDllHandle(v_dllHandle);
		v_dllHandle = NULL;
	}
}
#pragma endregion Unload DLL

