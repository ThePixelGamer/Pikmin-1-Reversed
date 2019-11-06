#ifndef MODULE_H
#define MODULE_H

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#include <sysCore.h>
#include <windows.h>

void MODULEPRINT(const char* fmt, ...);

struct MenuPlugin
{
    WPARAM prev;      // 0h
    char* name;       // 4h
    MenuPlugin* next; // 8h

    MenuPlugin() : next(nullptr) {}

    void setNext(MenuPlugin* nxt)
    {
        nxt->next = this->next;
        this->next = nxt;
    }
};

struct Object
{
    char* str;
    bool load;
    void* funcPtr;

    Object(char* s, bool l, void* f) : str(s), load(l), funcPtr(f) {}
};

typedef Object* (*DLLFuncVoid)();
typedef void* (*DLLFuncChar)(char*);
typedef int (*allocFunc)(void);

class SYSCORE_API Module
{
public:
    DLLFuncChar m_newObjAddr;    // 0h
    DLLFuncVoid m_objListAddr;   // 4h
    DLLFuncVoid m_autoStartAddr; // 8h
    HMODULE pHInstance;          // Ch
    char* libName;               // 10h
    Module* prev;                // 14h
    Module* next;                // 18h

    void Load(char*);
    void menuPlugins(MenuPlugin*, HMENU);
    ~Module();
};

#endif