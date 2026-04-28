// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TokenDataSubsystem.h"
#include "Engine/GameInstance.h"
#include "TokenData.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeTokenDataSubsystem() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UGameInstanceSubsystem();
TOKENRECEIVER_API UClass* Z_Construct_UClass_UTokenDataSubsystem();
TOKENRECEIVER_API UClass* Z_Construct_UClass_UTokenDataSubsystem_NoRegister();
TOKENRECEIVER_API UFunction* Z_Construct_UDelegateFunction_TokenReceiver_OnTokenReceived__DelegateSignature();
TOKENRECEIVER_API UScriptStruct* Z_Construct_UScriptStruct_FTokenData();
UPackage* Z_Construct_UPackage__Script_TokenReceiver();
// ********** End Cross Module References **********************************************************

// ********** Begin Delegate FOnTokenReceived ******************************************************
struct Z_Construct_UDelegateFunction_TokenReceiver_OnTokenReceived__DelegateSignature_Statics
{
	struct _Script_TokenReceiver_eventOnTokenReceived_Parms
	{
		FTokenData Data;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/TokenDataSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Data_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnTokenReceived constinit property declarations **********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Data;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FOnTokenReceived constinit property declarations ************************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FOnTokenReceived Property Definitions *********************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_TokenReceiver_OnTokenReceived__DelegateSignature_Statics::NewProp_Data = { "Data", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_TokenReceiver_eventOnTokenReceived_Parms, Data), Z_Construct_UScriptStruct_FTokenData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Data_MetaData), NewProp_Data_MetaData) }; // 4006304013
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_TokenReceiver_OnTokenReceived__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_TokenReceiver_OnTokenReceived__DelegateSignature_Statics::NewProp_Data,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_TokenReceiver_OnTokenReceived__DelegateSignature_Statics::PropPointers) < 2048);
// ********** End Delegate FOnTokenReceived Property Definitions ***********************************
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_TokenReceiver_OnTokenReceived__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_TokenReceiver, nullptr, "OnTokenReceived__DelegateSignature", 	Z_Construct_UDelegateFunction_TokenReceiver_OnTokenReceived__DelegateSignature_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_TokenReceiver_OnTokenReceived__DelegateSignature_Statics::PropPointers), 
sizeof(Z_Construct_UDelegateFunction_TokenReceiver_OnTokenReceived__DelegateSignature_Statics::_Script_TokenReceiver_eventOnTokenReceived_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00530000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_TokenReceiver_OnTokenReceived__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_TokenReceiver_OnTokenReceived__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_TokenReceiver_OnTokenReceived__DelegateSignature_Statics::_Script_TokenReceiver_eventOnTokenReceived_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_TokenReceiver_OnTokenReceived__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_TokenReceiver_OnTokenReceived__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnTokenReceived_DelegateWrapper(const FMulticastScriptDelegate& OnTokenReceived, FTokenData const& Data)
{
	struct _Script_TokenReceiver_eventOnTokenReceived_Parms
	{
		FTokenData Data;
	};
	_Script_TokenReceiver_eventOnTokenReceived_Parms Parms;
	Parms.Data=Data;
	OnTokenReceived.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FOnTokenReceived ********************************************************

// ********** Begin Class UTokenDataSubsystem Function AutoOpenPort ********************************
struct Z_Construct_UFunction_UTokenDataSubsystem_AutoOpenPort_Statics
{
	struct TokenDataSubsystem_eventAutoOpenPort_Parms
	{
		int32 BaudRate;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Token" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Scan for an Espressif USB device (VID 0x303A) and open it automatically. */" },
#endif
		{ "CPP_Default_BaudRate", "115200" },
		{ "ModuleRelativePath", "Public/TokenDataSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Scan for an Espressif USB device (VID 0x303A) and open it automatically." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function AutoOpenPort constinit property declarations **************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_BaudRate;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AutoOpenPort constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AutoOpenPort Property Definitions *************************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UTokenDataSubsystem_AutoOpenPort_Statics::NewProp_BaudRate = { "BaudRate", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TokenDataSubsystem_eventAutoOpenPort_Parms, BaudRate), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UTokenDataSubsystem_AutoOpenPort_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTokenDataSubsystem_AutoOpenPort_Statics::NewProp_BaudRate,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UTokenDataSubsystem_AutoOpenPort_Statics::PropPointers) < 2048);
// ********** End Function AutoOpenPort Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UTokenDataSubsystem_AutoOpenPort_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UTokenDataSubsystem, nullptr, "AutoOpenPort", 	Z_Construct_UFunction_UTokenDataSubsystem_AutoOpenPort_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UTokenDataSubsystem_AutoOpenPort_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UTokenDataSubsystem_AutoOpenPort_Statics::TokenDataSubsystem_eventAutoOpenPort_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UTokenDataSubsystem_AutoOpenPort_Statics::Function_MetaDataParams), Z_Construct_UFunction_UTokenDataSubsystem_AutoOpenPort_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UTokenDataSubsystem_AutoOpenPort_Statics::TokenDataSubsystem_eventAutoOpenPort_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UTokenDataSubsystem_AutoOpenPort()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UTokenDataSubsystem_AutoOpenPort_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UTokenDataSubsystem::execAutoOpenPort)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_BaudRate);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->AutoOpenPort(Z_Param_BaudRate);
	P_NATIVE_END;
}
// ********** End Class UTokenDataSubsystem Function AutoOpenPort **********************************

// ********** Begin Class UTokenDataSubsystem Function ClosePort ***********************************
struct Z_Construct_UFunction_UTokenDataSubsystem_ClosePort_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Token" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Close the serial port. Called automatically on subsystem shutdown. */" },
#endif
		{ "ModuleRelativePath", "Public/TokenDataSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Close the serial port. Called automatically on subsystem shutdown." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ClosePort constinit property declarations *****************************
// ********** End Function ClosePort constinit property declarations *******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UTokenDataSubsystem_ClosePort_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UTokenDataSubsystem, nullptr, "ClosePort", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UTokenDataSubsystem_ClosePort_Statics::Function_MetaDataParams), Z_Construct_UFunction_UTokenDataSubsystem_ClosePort_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UTokenDataSubsystem_ClosePort()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UTokenDataSubsystem_ClosePort_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UTokenDataSubsystem::execClosePort)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ClosePort();
	P_NATIVE_END;
}
// ********** End Class UTokenDataSubsystem Function ClosePort *************************************

// ********** Begin Class UTokenDataSubsystem Function IsConnected *********************************
struct Z_Construct_UFunction_UTokenDataSubsystem_IsConnected_Statics
{
	struct TokenDataSubsystem_eventIsConnected_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Token" },
		{ "ModuleRelativePath", "Public/TokenDataSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsConnected constinit property declarations ***************************
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsConnected constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsConnected Property Definitions **************************************
void Z_Construct_UFunction_UTokenDataSubsystem_IsConnected_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((TokenDataSubsystem_eventIsConnected_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UTokenDataSubsystem_IsConnected_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(TokenDataSubsystem_eventIsConnected_Parms), &Z_Construct_UFunction_UTokenDataSubsystem_IsConnected_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UTokenDataSubsystem_IsConnected_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTokenDataSubsystem_IsConnected_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UTokenDataSubsystem_IsConnected_Statics::PropPointers) < 2048);
// ********** End Function IsConnected Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UTokenDataSubsystem_IsConnected_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UTokenDataSubsystem, nullptr, "IsConnected", 	Z_Construct_UFunction_UTokenDataSubsystem_IsConnected_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UTokenDataSubsystem_IsConnected_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UTokenDataSubsystem_IsConnected_Statics::TokenDataSubsystem_eventIsConnected_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UTokenDataSubsystem_IsConnected_Statics::Function_MetaDataParams), Z_Construct_UFunction_UTokenDataSubsystem_IsConnected_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UTokenDataSubsystem_IsConnected_Statics::TokenDataSubsystem_eventIsConnected_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UTokenDataSubsystem_IsConnected()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UTokenDataSubsystem_IsConnected_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UTokenDataSubsystem::execIsConnected)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsConnected();
	P_NATIVE_END;
}
// ********** End Class UTokenDataSubsystem Function IsConnected ***********************************

// ********** Begin Class UTokenDataSubsystem Function OpenPort ************************************
struct Z_Construct_UFunction_UTokenDataSubsystem_OpenPort_Statics
{
	struct TokenDataSubsystem_eventOpenPort_Parms
	{
		FString PortName;
		int32 BaudRate;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Token" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Open a specific port by name, e.g. \"COM16\". Fallback if auto-detect fails. */" },
#endif
		{ "CPP_Default_BaudRate", "115200" },
		{ "ModuleRelativePath", "Public/TokenDataSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Open a specific port by name, e.g. \"COM16\". Fallback if auto-detect fails." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PortName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function OpenPort constinit property declarations ******************************
	static const UECodeGen_Private::FStrPropertyParams NewProp_PortName;
	static const UECodeGen_Private::FIntPropertyParams NewProp_BaudRate;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function OpenPort constinit property declarations ********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function OpenPort Property Definitions *****************************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UTokenDataSubsystem_OpenPort_Statics::NewProp_PortName = { "PortName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TokenDataSubsystem_eventOpenPort_Parms, PortName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PortName_MetaData), NewProp_PortName_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UTokenDataSubsystem_OpenPort_Statics::NewProp_BaudRate = { "BaudRate", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TokenDataSubsystem_eventOpenPort_Parms, BaudRate), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UTokenDataSubsystem_OpenPort_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTokenDataSubsystem_OpenPort_Statics::NewProp_PortName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTokenDataSubsystem_OpenPort_Statics::NewProp_BaudRate,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UTokenDataSubsystem_OpenPort_Statics::PropPointers) < 2048);
// ********** End Function OpenPort Property Definitions *******************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UTokenDataSubsystem_OpenPort_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UTokenDataSubsystem, nullptr, "OpenPort", 	Z_Construct_UFunction_UTokenDataSubsystem_OpenPort_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UTokenDataSubsystem_OpenPort_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UTokenDataSubsystem_OpenPort_Statics::TokenDataSubsystem_eventOpenPort_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UTokenDataSubsystem_OpenPort_Statics::Function_MetaDataParams), Z_Construct_UFunction_UTokenDataSubsystem_OpenPort_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UTokenDataSubsystem_OpenPort_Statics::TokenDataSubsystem_eventOpenPort_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UTokenDataSubsystem_OpenPort()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UTokenDataSubsystem_OpenPort_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UTokenDataSubsystem::execOpenPort)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_PortName);
	P_GET_PROPERTY(FIntProperty,Z_Param_BaudRate);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OpenPort(Z_Param_PortName,Z_Param_BaudRate);
	P_NATIVE_END;
}
// ********** End Class UTokenDataSubsystem Function OpenPort **************************************

// ********** Begin Class UTokenDataSubsystem ******************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UTokenDataSubsystem;
UClass* UTokenDataSubsystem::GetPrivateStaticClass()
{
	using TClass = UTokenDataSubsystem;
	if (!Z_Registration_Info_UClass_UTokenDataSubsystem.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("TokenDataSubsystem"),
			Z_Registration_Info_UClass_UTokenDataSubsystem.InnerSingleton,
			StaticRegisterNativesUTokenDataSubsystem,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UTokenDataSubsystem.InnerSingleton;
}
UClass* Z_Construct_UClass_UTokenDataSubsystem_NoRegister()
{
	return UTokenDataSubsystem::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UTokenDataSubsystem_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * GameInstance subsystem \xe2\x80\x94 opens a USB serial port and fires OnTokenReceived\n * on the game thread for every valid token message received.\n *\n * Blueprint usage:\n *   1. Get Game Instance Subsystem (TokenDataSubsystem)\n *   2. Call AutoOpenPort() \xe2\x80\x94 finds the receiver ESP32-C6 automatically\n *   3. Bind event to OnTokenReceived\n *   4. Read FTokenData fields (Timestamp, TokenId, Sensor0\xe2\x80\x93""3, BatteryMv)\n */" },
#endif
		{ "IncludePath", "TokenDataSubsystem.h" },
		{ "ModuleRelativePath", "Public/TokenDataSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "GameInstance subsystem \xe2\x80\x94 opens a USB serial port and fires OnTokenReceived\non the game thread for every valid token message received.\n\nBlueprint usage:\n  1. Get Game Instance Subsystem (TokenDataSubsystem)\n  2. Call AutoOpenPort() \xe2\x80\x94 finds the receiver ESP32-C6 automatically\n  3. Bind event to OnTokenReceived\n  4. Read FTokenData fields (Timestamp, TokenId, Sensor0\xe2\x80\x93""3, BatteryMv)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnTokenReceived_MetaData[] = {
		{ "Category", "Token" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Fired on the game thread for each received token message\n" },
#endif
		{ "ModuleRelativePath", "Public/TokenDataSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Fired on the game thread for each received token message" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UTokenDataSubsystem constinit property declarations **********************
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnTokenReceived;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UTokenDataSubsystem constinit property declarations ************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("AutoOpenPort"), .Pointer = &UTokenDataSubsystem::execAutoOpenPort },
		{ .NameUTF8 = UTF8TEXT("ClosePort"), .Pointer = &UTokenDataSubsystem::execClosePort },
		{ .NameUTF8 = UTF8TEXT("IsConnected"), .Pointer = &UTokenDataSubsystem::execIsConnected },
		{ .NameUTF8 = UTF8TEXT("OpenPort"), .Pointer = &UTokenDataSubsystem::execOpenPort },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UTokenDataSubsystem_AutoOpenPort, "AutoOpenPort" }, // 1422799757
		{ &Z_Construct_UFunction_UTokenDataSubsystem_ClosePort, "ClosePort" }, // 1006145025
		{ &Z_Construct_UFunction_UTokenDataSubsystem_IsConnected, "IsConnected" }, // 3909765051
		{ &Z_Construct_UFunction_UTokenDataSubsystem_OpenPort, "OpenPort" }, // 1753564460
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UTokenDataSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UTokenDataSubsystem_Statics

// ********** Begin Class UTokenDataSubsystem Property Definitions *********************************
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UTokenDataSubsystem_Statics::NewProp_OnTokenReceived = { "OnTokenReceived", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UTokenDataSubsystem, OnTokenReceived), Z_Construct_UDelegateFunction_TokenReceiver_OnTokenReceived__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnTokenReceived_MetaData), NewProp_OnTokenReceived_MetaData) }; // 2874533211
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UTokenDataSubsystem_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTokenDataSubsystem_Statics::NewProp_OnTokenReceived,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTokenDataSubsystem_Statics::PropPointers) < 2048);
// ********** End Class UTokenDataSubsystem Property Definitions ***********************************
UObject* (*const Z_Construct_UClass_UTokenDataSubsystem_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UGameInstanceSubsystem,
	(UObject* (*)())Z_Construct_UPackage__Script_TokenReceiver,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTokenDataSubsystem_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UTokenDataSubsystem_Statics::ClassParams = {
	&UTokenDataSubsystem::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UTokenDataSubsystem_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UTokenDataSubsystem_Statics::PropPointers),
	0,
	0x009000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UTokenDataSubsystem_Statics::Class_MetaDataParams), Z_Construct_UClass_UTokenDataSubsystem_Statics::Class_MetaDataParams)
};
void UTokenDataSubsystem::StaticRegisterNativesUTokenDataSubsystem()
{
	UClass* Class = UTokenDataSubsystem::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UTokenDataSubsystem_Statics::Funcs));
}
UClass* Z_Construct_UClass_UTokenDataSubsystem()
{
	if (!Z_Registration_Info_UClass_UTokenDataSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UTokenDataSubsystem.OuterSingleton, Z_Construct_UClass_UTokenDataSubsystem_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UTokenDataSubsystem.OuterSingleton;
}
UTokenDataSubsystem::UTokenDataSubsystem() {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UTokenDataSubsystem);
UTokenDataSubsystem::~UTokenDataSubsystem() {}
// ********** End Class UTokenDataSubsystem ********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_finn_Documents_Unreal_Projects_CoralPlugin_Plugins_TokenReceiver_Source_TokenReceiver_Public_TokenDataSubsystem_h__Script_TokenReceiver_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UTokenDataSubsystem, UTokenDataSubsystem::StaticClass, TEXT("UTokenDataSubsystem"), &Z_Registration_Info_UClass_UTokenDataSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UTokenDataSubsystem), 366924748U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_finn_Documents_Unreal_Projects_CoralPlugin_Plugins_TokenReceiver_Source_TokenReceiver_Public_TokenDataSubsystem_h__Script_TokenReceiver_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_finn_Documents_Unreal_Projects_CoralPlugin_Plugins_TokenReceiver_Source_TokenReceiver_Public_TokenDataSubsystem_h__Script_TokenReceiver_3836520156{
	TEXT("/Script/TokenReceiver"),
	Z_CompiledInDeferFile_FID_Users_finn_Documents_Unreal_Projects_CoralPlugin_Plugins_TokenReceiver_Source_TokenReceiver_Public_TokenDataSubsystem_h__Script_TokenReceiver_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_finn_Documents_Unreal_Projects_CoralPlugin_Plugins_TokenReceiver_Source_TokenReceiver_Public_TokenDataSubsystem_h__Script_TokenReceiver_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
