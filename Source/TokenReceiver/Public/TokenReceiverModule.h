#pragma once
#include "Modules/ModuleInterface.h"

class ITokenReceiverModule : public IModuleInterface
{
public:
    static ITokenReceiverModule& Get()
    {
        return FModuleManager::LoadModuleChecked<ITokenReceiverModule>("TokenReceiver");
    }
};
