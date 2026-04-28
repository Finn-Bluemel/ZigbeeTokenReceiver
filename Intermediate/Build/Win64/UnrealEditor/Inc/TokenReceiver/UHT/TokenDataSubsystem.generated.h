// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "TokenDataSubsystem.h"

#ifdef TOKENRECEIVER_TokenDataSubsystem_generated_h
#error "TokenDataSubsystem.generated.h already included, missing '#pragma once' in TokenDataSubsystem.h"
#endif
#define TOKENRECEIVER_TokenDataSubsystem_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FTokenData;

// ********** Begin Delegate FOnTokenReceived ******************************************************
#define FID_Users_finn_Documents_Unreal_Projects_CoralPlugin_Plugins_TokenReceiver_Source_TokenReceiver_Public_TokenDataSubsystem_h_9_DELEGATE \
TOKENRECEIVER_API void FOnTokenReceived_DelegateWrapper(const FMulticastScriptDelegate& OnTokenReceived, FTokenData const& Data);


// ********** End Delegate FOnTokenReceived ********************************************************

// ********** Begin Class UTokenDataSubsystem ******************************************************
#define FID_Users_finn_Documents_Unreal_Projects_CoralPlugin_Plugins_TokenReceiver_Source_TokenReceiver_Public_TokenDataSubsystem_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execIsConnected); \
	DECLARE_FUNCTION(execClosePort); \
	DECLARE_FUNCTION(execOpenPort); \
	DECLARE_FUNCTION(execAutoOpenPort);


struct Z_Construct_UClass_UTokenDataSubsystem_Statics;
TOKENRECEIVER_API UClass* Z_Construct_UClass_UTokenDataSubsystem_NoRegister();

#define FID_Users_finn_Documents_Unreal_Projects_CoralPlugin_Plugins_TokenReceiver_Source_TokenReceiver_Public_TokenDataSubsystem_h_24_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUTokenDataSubsystem(); \
	friend struct ::Z_Construct_UClass_UTokenDataSubsystem_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend TOKENRECEIVER_API UClass* ::Z_Construct_UClass_UTokenDataSubsystem_NoRegister(); \
public: \
	DECLARE_CLASS2(UTokenDataSubsystem, UGameInstanceSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/TokenReceiver"), Z_Construct_UClass_UTokenDataSubsystem_NoRegister) \
	DECLARE_SERIALIZER(UTokenDataSubsystem)


#define FID_Users_finn_Documents_Unreal_Projects_CoralPlugin_Plugins_TokenReceiver_Source_TokenReceiver_Public_TokenDataSubsystem_h_24_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UTokenDataSubsystem(); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UTokenDataSubsystem(UTokenDataSubsystem&&) = delete; \
	UTokenDataSubsystem(const UTokenDataSubsystem&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UTokenDataSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UTokenDataSubsystem); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UTokenDataSubsystem) \
	NO_API virtual ~UTokenDataSubsystem();


#define FID_Users_finn_Documents_Unreal_Projects_CoralPlugin_Plugins_TokenReceiver_Source_TokenReceiver_Public_TokenDataSubsystem_h_21_PROLOG
#define FID_Users_finn_Documents_Unreal_Projects_CoralPlugin_Plugins_TokenReceiver_Source_TokenReceiver_Public_TokenDataSubsystem_h_24_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_finn_Documents_Unreal_Projects_CoralPlugin_Plugins_TokenReceiver_Source_TokenReceiver_Public_TokenDataSubsystem_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_finn_Documents_Unreal_Projects_CoralPlugin_Plugins_TokenReceiver_Source_TokenReceiver_Public_TokenDataSubsystem_h_24_INCLASS_NO_PURE_DECLS \
	FID_Users_finn_Documents_Unreal_Projects_CoralPlugin_Plugins_TokenReceiver_Source_TokenReceiver_Public_TokenDataSubsystem_h_24_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UTokenDataSubsystem;

// ********** End Class UTokenDataSubsystem ********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_finn_Documents_Unreal_Projects_CoralPlugin_Plugins_TokenReceiver_Source_TokenReceiver_Public_TokenDataSubsystem_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
