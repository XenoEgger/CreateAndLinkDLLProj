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

	UFUNCTION(BlueprintCallable, Category = "My DLL Library")
	static bool importMethodGetCharArray();
	


	UFUNCTION(BlueprintCallable, Category = "My DLL Library")
	static bool getInvertedBoolFromDll(bool boolState);

	UFUNCTION(BlueprintCallable, Category = "My DLL Library")
	static int getIntPlusPlusFromDll(int lastInt);

	UFUNCTION(BlueprintCallable, Category = "My DLL Library")
	static float getCircleAreaFromDll(float radius);

	UFUNCTION(BlueprintCallable, Category = "My DLL Library")
	static FString getCharArrayFromDll(FString parameterText);
	


	UFUNCTION(BlueprintCallable, Category = "My DLL Library")
	static void freeDLL();
};
