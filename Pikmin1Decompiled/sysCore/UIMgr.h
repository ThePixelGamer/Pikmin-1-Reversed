#ifndef UIMGR_H
#define UIMGR_H
#pragma once
#include "..\Externals.h"
#include <CommCtrl.h>
#include <Windows.h>
#pragma comment(lib, "Comctl32.lib")

class UIMgr
{
private:
public:
	UIMgr();
	~UIMgr();

	void RegisterGenWindowClass(LPCSTR, void *, bool);
};
#endif