// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TokenData.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeTokenData() {}

// ********** Begin Cross Module References ********************************************************
TOKENRECEIVER_API UScriptStruct* Z_Construct_UScriptStruct_FTokenData();
UPackage* Z_Construct_UPackage__Script_TokenReceiver();
// ********** End Cross Module References **********************************************************

// ********** Begin ScriptStruct FTokenData ********************************************************
struct Z_Construct_UScriptStruct_FTokenData_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FTokenData); }
	static inline consteval int16 GetStructAlignment() { return alignof(FTokenData); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/TokenData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RawMessage_MetaData[] = {
		{ "Category", "Token" },
		{ "ModuleRelativePath", "Public/TokenData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Timestamp_MetaData[] = {
		{ "Category", "Token" },
		{ "ModuleRelativePath", "Public/TokenData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TokenId_MetaData[] = {
		{ "Category", "Token" },
		{ "ModuleRelativePath", "Public/TokenData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Sensor0_MetaData[] = {
		{ "Category", "Token" },
		{ "ModuleRelativePath", "Public/TokenData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Sensor1_MetaData[] = {
		{ "Category", "Token" },
		{ "ModuleRelativePath", "Public/TokenData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Sensor2_MetaData[] = {
		{ "Category", "Token" },
		{ "ModuleRelativePath", "Public/TokenData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Sensor3_MetaData[] = {
		{ "Category", "Token" },
		{ "ModuleRelativePath", "Public/TokenData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BatteryMv_MetaData[] = {
		{ "Category", "Token" },
		{ "ModuleRelativePath", "Public/TokenData.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FTokenData constinit property declarations ************************
	static const UECodeGen_Private::FStrPropertyParams NewProp_RawMessage;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Timestamp;
	static const UECodeGen_Private::FIntPropertyParams NewProp_TokenId;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Sensor0;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Sensor1;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Sensor2;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Sensor3;
	static const UECodeGen_Private::FIntPropertyParams NewProp_BatteryMv;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FTokenData constinit property declarations **************************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTokenData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FTokenData_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FTokenData;
class UScriptStruct* FTokenData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FTokenData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FTokenData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FTokenData, (UObject*)Z_Construct_UPackage__Script_TokenReceiver(), TEXT("TokenData"));
	}
	return Z_Registration_Info_UScriptStruct_FTokenData.OuterSingleton;
	}

// ********** Begin ScriptStruct FTokenData Property Definitions ***********************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FTokenData_Statics::NewProp_RawMessage = { "RawMessage", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTokenData, RawMessage), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RawMessage_MetaData), NewProp_RawMessage_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FTokenData_Statics::NewProp_Timestamp = { "Timestamp", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTokenData, Timestamp), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Timestamp_MetaData), NewProp_Timestamp_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FTokenData_Statics::NewProp_TokenId = { "TokenId", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTokenData, TokenId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TokenId_MetaData), NewProp_TokenId_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FTokenData_Statics::NewProp_Sensor0 = { "Sensor0", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTokenData, Sensor0), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Sensor0_MetaData), NewProp_Sensor0_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FTokenData_Statics::NewProp_Sensor1 = { "Sensor1", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTokenData, Sensor1), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Sensor1_MetaData), NewProp_Sensor1_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FTokenData_Statics::NewProp_Sensor2 = { "Sensor2", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTokenData, Sensor2), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Sensor2_MetaData), NewProp_Sensor2_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FTokenData_Statics::NewProp_Sensor3 = { "Sensor3", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTokenData, Sensor3), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Sensor3_MetaData), NewProp_Sensor3_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FTokenData_Statics::NewProp_BatteryMv = { "BatteryMv", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTokenData, BatteryMv), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BatteryMv_MetaData), NewProp_BatteryMv_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FTokenData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTokenData_Statics::NewProp_RawMessage,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTokenData_Statics::NewProp_Timestamp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTokenData_Statics::NewProp_TokenId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTokenData_Statics::NewProp_Sensor0,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTokenData_Statics::NewProp_Sensor1,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTokenData_Statics::NewProp_Sensor2,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTokenData_Statics::NewProp_Sensor3,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTokenData_Statics::NewProp_BatteryMv,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTokenData_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FTokenData Property Definitions *************************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTokenData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_TokenReceiver,
	nullptr,
	&NewStructOps,
	"TokenData",
	Z_Construct_UScriptStruct_FTokenData_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTokenData_Statics::PropPointers),
	sizeof(FTokenData),
	alignof(FTokenData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTokenData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FTokenData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FTokenData()
{
	if (!Z_Registration_Info_UScriptStruct_FTokenData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FTokenData.InnerSingleton, Z_Construct_UScriptStruct_FTokenData_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FTokenData.InnerSingleton);
}
// ********** End ScriptStruct FTokenData **********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_finn_Documents_Unreal_Projects_CoralPlugin_Plugins_TokenReceiver_Source_TokenReceiver_Public_TokenData_h__Script_TokenReceiver_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FTokenData::StaticStruct, Z_Construct_UScriptStruct_FTokenData_Statics::NewStructOps, TEXT("TokenData"),&Z_Registration_Info_UScriptStruct_FTokenData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FTokenData), 4006304013U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_finn_Documents_Unreal_Projects_CoralPlugin_Plugins_TokenReceiver_Source_TokenReceiver_Public_TokenData_h__Script_TokenReceiver_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_finn_Documents_Unreal_Projects_CoralPlugin_Plugins_TokenReceiver_Source_TokenReceiver_Public_TokenData_h__Script_TokenReceiver_1559857568{
	TEXT("/Script/TokenReceiver"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Users_finn_Documents_Unreal_Projects_CoralPlugin_Plugins_TokenReceiver_Source_TokenReceiver_Public_TokenData_h__Script_TokenReceiver_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_finn_Documents_Unreal_Projects_CoralPlugin_Plugins_TokenReceiver_Source_TokenReceiver_Public_TokenData_h__Script_TokenReceiver_Statics::ScriptStructInfo),
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
