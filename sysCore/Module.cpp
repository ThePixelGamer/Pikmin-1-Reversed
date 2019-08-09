#include "Module.h"

//////////////////////////////////////////////////////////////////////
// Module class functions
//////////////////////////////////////////////////////////////////////

void printModuleMgr(const char* fmt, ...) {
	char* dest;
	va_list args;
	va_start(args, fmt);

	if(sysCon) {
		sysCon->print("%s: ", "moduleMgr");
		vsprintf(dest, fmt, args);
		if(strlen(dest)) {
			sysCon->write(dest, strlen(dest));
		}
	}
}

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
	printModuleMgr("opening %s\n", this->libName);

	this->pHInstance = LoadLibraryA(this->libName);
	if (this->pHInstance) {
		this->m_newObjAddr = GetProcAddress(this->pHInstance, "NewObject");
		this->m_objListAddr = GetProcAddress(this->pHInstance, "GetObjectList");
		this->m_autoStartAddr = GetProcAddress(this->pHInstance, "AutoStart");
	}
	else {
		this->m_newObjAddr = 0;
		this->m_objListAddr = 0;
		this->m_autoStartAddr = 0;
	}
}

void Module::menuPlugins(MenuPlugin* unused, HMENU hmenu) {
	int unk1, unk2, unk3;

	for(Object* i = (Object*)(this->m_objListAddr)(); i; i++) {
		if(i->unk) {
			RegisterWindowMessageA(i->str);
			//hmenu = globalHeapAllocator();

		}
	}
}

//////////////////////////////////////////////////////////////////////
// ModuleMgr class functions
//////////////////////////////////////////////////////////////////////

SYSCORE_API ModuleMgr* modMgr;

ModuleMgr::ModuleMgr() {}

ModuleMgr::~ModuleMgr() {

}

void ModuleMgr::Alloc(char* a2) {
	
}

void ModuleMgr::UnLoad() {
	
}

void ModuleMgr::findModule() {
	
}

void ModuleMgr::listModules() {
	
}

Module* ModuleMgr::loadModule(char* a2) {
	return 0;
}
