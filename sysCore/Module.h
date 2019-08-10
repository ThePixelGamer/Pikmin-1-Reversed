#ifndef MODULE_H
#define MODULE_H

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#include <windows.h>
#include "sysCore.h"

struct MenuPlugin {
	WPARAM wParam; // 0h
	char* name; // 4h
	MenuPlugin* next; // 8h
};

struct Object { 
	char* str; 
	bool load; 
	void* ptrToClass; 
};

class SYSCORE_API Module {
public:
	FARPROC m_newObjAddr; //0h
	FARPROC m_objListAddr; //4h
	FARPROC m_autoStartAddr; //8h
	HMODULE pHInstance; //Ch
	char* libName; //10h

	void Load(char*);
	void menuPlugins(MenuPlugin*, HMENU);
	~Module();
};

class SYSCORE_API ModuleMgr {
public:
	Module* unk3 = new Module();
	ModuleMgr* unk1; //14h
	ModuleMgr* unk2; //18h

	ModuleMgr();
	~ModuleMgr();

	void Alloc(char*);
	void UnLoad();
	void findModule();
	void listModules();
	Module* loadModule(char*);
};

extern SYSCORE_API ModuleMgr* modMgr;

#endif 