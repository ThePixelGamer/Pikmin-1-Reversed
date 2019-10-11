#ifndef MODULE_H
#define MODULE_H

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#include "sysCore.h"
#include <windows.h>

struct MenuPlugin {
  WPARAM prev;      // 0h
  char *name;       // 4h
  MenuPlugin *next; // 8h

  MenuPlugin() : next(0) {}

  void setNext(MenuPlugin *nxt) {
    nxt->next = this->next;
    this->next = nxt;
  }
};

struct Object {
  char *str;
  bool load;
  void *funcPtr;
};

typedef Object *(*DLLFuncVoid)();
typedef void *(*DLLFuncChar)(char *);
typedef int (*allocFunc)(void);

class SYSCORE_API Module {
public:
  DLLFuncChar m_newObjAddr;    // 0h
  DLLFuncVoid m_objListAddr;   // 4h
  DLLFuncVoid m_autoStartAddr; // 8h
  HMODULE pHInstance;          // Ch
  char *libName;               // 10h
  Module *prev;                // 14h
  Module *next;                // 18h

  void Load(char *);
  void menuPlugins(MenuPlugin *, HMENU);
  ~Module();
};

class SYSCORE_API ModuleMgr {
public:
  Module *topModule;
  int moduleCount;

  ModuleMgr();
  ~ModuleMgr();

  void *Alloc(char *);
  void UnLoad(Module *);
  Module *findModule(char *);
  void listModules();
  Module *loadModule(char *);
};

extern SYSCORE_API ModuleMgr *modMgr;

#endif