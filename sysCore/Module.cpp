#include "Module.h"

void print(const char* fmt, ...) {
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
	print("opening %s\n", this->libName);

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

static int itemCount;

void Module::menuPlugins(MenuPlugin* unused, HMENU hmenu) {
	int unk1, unk2, unk3;

	for (Object* i = (Object*)(this->m_objListAddr)(); i; i++) {
		if (i->load) {
			UINT msg = RegisterWindowMessageA(i->str);
			//hmenu = globalHeapAllocator();
			MENUITEMINFO mi;
			//mi.hbmpItem = HBMMENU_SYSTEM;
			mi.cbSize = 44;
			mi.fMask = 18;
			mi.wID = msg;
			mi.fType = 0;
			mi.dwTypeData = i->str;
			mi.cch = strlen(i->str);
			int item = itemCount++;
			InsertMenuItemA(hmenu, item, 1, &mi);
		}
	}
}

//////////////////////////////////////////////////////////////////////
// ModuleMgr class functions
//////////////////////////////////////////////////////////////////////

SYSCORE_API ModuleMgr* modMgr;

ModuleMgr::ModuleMgr() { //very confusing
	//print("Creating moduleMgr ...\n");
	/*ModuleMgr* memory = new ModuleMgr();
	this->unk3 = ((memory != 0) ? memory->unk3 : 0);
	this->unk1 = memory;
	this->unk2 = this->unk1;*/
}

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
