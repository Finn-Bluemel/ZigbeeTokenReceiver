// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTokenReceiver_init() {}
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");	TOKENRECEIVER_API UFunction* Z_Construct_UDelegateFunction_TokenReceiver_OnTokenReceived__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_TokenReceiver;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_TokenReceiver()
	{
		if (!Z_Registration_Info_UPackage__Script_TokenReceiver.OuterSingleton)
		{
		static UObject* (*const SingletonFuncArray[])() = {
			(UObject* (*)())Z_Construct_UDelegateFunction_TokenReceiver_OnTokenReceived__DelegateSignature,
		};
		static const UECodeGen_Private::FPackageParams PackageParams = {
			"/Script/TokenReceiver",
			SingletonFuncArray,
			UE_ARRAY_COUNT(SingletonFuncArray),
			PKG_CompiledIn | 0x00000000,
			0x477BF052,
			0x459040A2,
			METADATA_PARAMS(0, nullptr)
		};
		UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_TokenReceiver.OuterSingleton, PackageParams);
	}
	return Z_Registration_Info_UPackage__Script_TokenReceiver.OuterSingleton;
}
static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_TokenReceiver(Z_Construct_UPackage__Script_TokenReceiver, TEXT("/Script/TokenReceiver"), Z_Registration_Info_UPackage__Script_TokenReceiver, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x477BF052, 0x459040A2));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
