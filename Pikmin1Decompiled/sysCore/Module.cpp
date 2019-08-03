// Module.cpp: implementation of the Module class.
//
//////////////////////////////////////////////////////////////////////

#include "Module.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
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

Module::~Module()
{
	if (this->pHInstance)
	{
		this->m_newObjAddr = 0;
		this->m_autoStartAddr = 0;
		FreeLibrary(this->pHInstance);
		this->pHInstance = 0;
		free(this->libName);
	}
}

void Module::Load(char * source)
{
	this->libName = strdup(source);
	printModuleMgr("opening %s\n", this->libName);

	this->pHInstance = LoadLibrary(this->libName);
	if (this->pHInstance)
	{
		this->m_newObjAddr = GetProcAddress(this->pHInstance, "NewObject");
		this->m_objListAddr = GetProcAddress(this->pHInstance, "GetObjectList");
		this->m_autoStartAddr = GetProcAddress(this->pHInstance, "AutoStart");
	}
	else
	{
		this->m_newObjAddr = 0;
		this->m_objListAddr = 0;
		this->m_autoStartAddr = 0;
	}
}

void Module::menuPlugins(struct MenuPlugin * unused, HMENU hmenu)
{

}