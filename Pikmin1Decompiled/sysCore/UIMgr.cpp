#include "UIMgr.h"

UIMgr::UIMgr()
{
	InitCommonControls();
}

UIMgr::~UIMgr()
{
}

void UIMgr::RegisterGenWindowClass(LPCSTR szClass, void* unkBuf, bool unk)
{
	LRESULT (__stdcall *funcCallBack)(HWND, UINT, WPARAM, LPARAM);
	WNDCLASSEXA wcx;

	if (!GetClassInfoExA(sysHInst, szClass, &wcx))
	{
		wcx.cbSize = 48;
		wcx.lpszClassName = szClass;
		wcx.hInstance = sysHInst;
		if (unkBuf)
			funcCallBack = unkBuf;
	}
}
