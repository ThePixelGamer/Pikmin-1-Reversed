#include "sysCore.h"

SYSCORE_API HINSTANCE hInstance;
SYSCORE_API HINSTANCE sysHInst;
SYSCORE_API Stream* sysCon;
SYSCORE_API class Stream* errCon;

BOOL __stdcall DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == 1)
		hInstance = hinstDLL;
	return TRUE;
}