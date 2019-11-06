#include <sysCore.h>
#include <Module/Module.h>
#define EXTERN_DLL_EXPORT extern "C" __declspec(dllexport)

BOOL __stdcall DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        hInstance = hinstDLL;
    }

    return 1;
}

extern Object ObjectList[];

EXTERN_DLL_EXPORT Object* GetObjectList()
{
    return (Object*)&ObjectList;
}

EXTERN_DLL_EXPORT Object* NewObject(char* name)
{
    for (Object* i = (Object*)&ObjectList; i->str; i++)
    {
        if (!strcmp(i->str, name))
            return ((Object* (*)(void))i->funcPtr)();
    }
    return 0;
}

EXTERN_DLL_EXPORT void AutoStart()
{
    
}