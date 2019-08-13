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
	WPARAM prev; // 0h
	char* name; // 4h
	MenuPlugin* next; // 8h

	MenuPlugin() : next(0) {}

	void setNext(MenuPlugin* nxt) {
		nxt->next = this->next;
		this->next = nxt;
	}
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
	Module* prev; //14h
	Module* next; //18h

	void Load(char*);
	void menuPlugins(MenuPlugin*, HMENU);
	~Module();
};

class SYSCORE_API ModuleMgr {
public:
	Module* unk3;
	int moduleCount;

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