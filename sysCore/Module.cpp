#include "Module.h"

void MODULEPRINT(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	char dest[1024];

	if (sysCon) {
		if ("ModuleMgr")
			sysCon->print("%s: ", "ModuleMgr");
		vsprintf(dest, fmt, args);
		if (strlen(dest)) {
			sysCon->write(dest, strlen(dest));
		}
	}
}

//////////////////////////////////////////////////////////////////////
// Module class functions
//////////////////////////////////////////////////////////////////////

Module::~Module() {
	if (this->pHInstance) {
		this->m_newObjAddr = 0;
		this->m_autoStartAddr = 0;
		FreeLibrary(this->pHInstance);
		this->pHInstance = 0;
		free(this->libName);
	}
}

void Module::Load(char* source) {
	this->libName = strdup(source);
	MODULEPRINT("opening %s\n", this->libName);

	this->pHInstance = LoadLibraryA(this->libName);
	if (this->pHInstance) {
		this->m_newObjAddr    = (DLLFuncChar)GetProcAddress(this->pHInstance, "NewObject"); //(char)
		this->m_objListAddr   = (DLLFuncVoid)GetProcAddress(this->pHInstance, "GetObjectList"); //(void)
		this->m_autoStartAddr = (DLLFuncVoid)GetProcAddress(this->pHInstance, "AutoStart"); //(void)
	}
	else {
		this->m_newObjAddr = 0;
		this->m_objListAddr = 0;
		this->m_autoStartAddr = 0;
	}
}

static int itemCount;

void Module::menuPlugins(MenuPlugin* menu, HMENU hmenu) {
	for (Object* i = (this->m_objListAddr)(); i->str; i++) {
		if (i->load) {
			UINT message = RegisterWindowMessageA(i->str);
			MenuPlugin* unk = new MenuPlugin();
			unk->prev = message;
			unk->name = i->str;
			menu->setNext(unk);

			MENUITEMINFO mi;
			mi.cbSize = sizeof(MENUITEMINFO);
			mi.fMask = MIIM_TYPE | MIIM_ID;
			mi.wID = message;
			mi.fType = MFT_STRING;
			mi.dwTypeData = i->str;
			mi.cch = strlen(i->str);
			InsertMenuItemA(hmenu, itemCount++, 1, &mi);
		}
	}
}

//////////////////////////////////////////////////////////////////////
// ModuleMgr class functions
//////////////////////////////////////////////////////////////////////

SYSCORE_API ModuleMgr* modMgr;

ModuleMgr::ModuleMgr() {
	MODULEPRINT("Creating moduleMgr ...\n");
	this->topModule = new Module();
	this->topModule->next = this->topModule;
	this->topModule->prev = this->topModule->next;
	this->moduleCount = 0;
}

ModuleMgr::~ModuleMgr() {
	Module* nxt;
	for(Module* i = this->topModule->prev; i != this->topModule;) {
		nxt = i->prev;
		this->UnLoad(i);
		i = nxt;
	}
}

void* ModuleMgr::Alloc(char* a2) {
	void* tmp;
	for(Module* i = this->topModule->prev; i != topModule; i = i->prev) {
		tmp = (i->m_newObjAddr)(a2);
		if(tmp) {
			return tmp;
		}
	}
	MODULEPRINT("ModuleMgr: !!!!! could not allocate %s !!!!!\n", a2);
	return 0;
}

void ModuleMgr::UnLoad(Module* a2) {
	a2->prev->next = a2->next;
	a2->next->prev = a2->prev;
	this->moduleCount--;
	delete a2;
}

Module* ModuleMgr::findModule(char* str) {
	for(Module* i = this->topModule->prev; i != this->topModule; i = i->prev) {
		if(!strcmp(i->libName, str))
			return i;
	}
	return 0;
}

void ModuleMgr::listModules() {
	if(this->topModule->prev == this->topModule) {}
	else {
		Module* i;
		
		char* unk = (this->moduleCount!=1) ? "es" : "e";

		for(i = this->topModule->prev; i != this->topModule; i = i->prev) {}
	}
}

Module* ModuleMgr::loadModule(char* a2) {
	Module* ret = this->findModule(a2);
	if(!ret) {
		ret = new Module();
		ret->Load(a2);
		ret->prev = this->topModule;
		ret->next = this->topModule->next;
		this->topModule->next = ret;
		ret->next->prev = ret;
		this->moduleCount++;

		if(ret->m_autoStartAddr) 
			(ret->m_autoStartAddr)();
	}

	return ret;
}
