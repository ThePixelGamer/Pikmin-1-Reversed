// Module.h: interface for the Module class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODULE_H__8E319D75_CC77_4434_9FF0_AD3F36E52715__INCLUDED_)
#define AFX_MODULE_H__8E319D75_CC77_4434_9FF0_AD3F36E52715__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include "sysCore.h"

class Module  
{
public:
	FARPROC m_newObjAddr; //0h
	FARPROC m_objListAddr; //4h
	FARPROC m_autoStartAddr; //8h
	HMODULE pHInstance; //Ch
	LPCSTR libName; //10h

	void Load(char * source);
	void menuPlugins(struct MenuPlugin *, HMENU hmenu);
	~Module();
};

class ModuleMgr
{

};

#endif // !defined(AFX_MODULE_H__8E319D75_CC77_4434_9FF0_AD3F36E52715__INCLUDED_)
