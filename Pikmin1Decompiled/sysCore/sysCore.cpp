#include "sysCore.h"

BOOL __stdcall DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
  if ( fdwReason == 1 )
    hInstance = hinstDLL;
  return TRUE;
}