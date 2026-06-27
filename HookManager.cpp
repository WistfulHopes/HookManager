#include "HookManager.hpp"

HookManager* HookManager::Instance = nullptr;

void HookManager::StaticInitialize()
{
    Instance = new HookManager();
}

void HookManager::StaticFinalize()
{
    delete Instance;
}

HookManager* HookManager::GetInstance()
{
    if (!Instance) StaticInitialize();
    return Instance;
}

void* HookManager::GetHook(const uintptr_t HookAddr) const
{
    for (auto& Hook : Hooks)
    {
        // there is no size difference between ManagedHook templates, so assume void with no args
        if (static_cast<ManagedHook<&Temp, void>*>(Hook.get())->GetAddr() == HookAddr)
        {
            return Hook.get();
        }
    }
    return nullptr;
}

void* HookManager::GetMidHook(const uintptr_t HookAddr) const
{
    for (auto& MidHook : MidHooks)
    {
        // there is no size difference between ManagedMidHook templates, so assume void with no args
        if (static_cast<ManagedMidHook<&Temp>*>(MidHook.get())->GetAddr() == HookAddr)
        {
            return MidHook.get();
        }
    }
    return nullptr;
}
