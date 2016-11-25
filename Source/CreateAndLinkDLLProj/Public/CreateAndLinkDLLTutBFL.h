
#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "CreateAndLinkDLLTutBFL.generated.h"


UCLASS()
class CREATEANDLINKDLLPROJ_API UCreateAndLinkDLLTutBFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "My DLL Library")
	static bool importDLL( FString folder, FString name);



	UFUNCTION(BlueprintCallable, Category = "My DLL Library")
	static bool importMethodGetInvertedBool();

	UFUNCTION(BlueprintCallable, Category = "My DLL Library")
	static bool importMethodGetIntPlusPlus();

	UFUNCTION(BlueprintCallable, Category = "My DLL Library")
	static bool importMethodGetCircleArea();
	
	//buggy
	UFUNCTION(BlueprintCallable, Category = "My DLL Library")
	static bool importMethodGetAdditionalString();



	UFUNCTION(BlueprintCallable, Category = "My DLL Library")
	static bool getInvertedBoolFromDll(bool boolState);

	UFUNCTION(BlueprintCallable, Category = "My DLL Library")
	static int getIntPlusPlusFromDll(int lastInt);

	UFUNCTION(BlueprintCallable, Category = "My DLL Library")
	static float getCircleAreaFromDll(float radius);

	//buggy
	UFUNCTION(BlueprintCallable, Category = "My DLL Library")
	static FString getAdditionalStringFromDll(FString baseString);
	


	UFUNCTION(BlueprintCallable, Category = "My DLL Library")
	static void freeDLL();
};
