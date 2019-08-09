#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef MODULE_H
#define MODULE_H

#include <windows.h>
#include "sysCore.h"

class MenuPlugin;

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

class ModuleMgr {

};

#endif 