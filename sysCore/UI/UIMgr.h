#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef UIMGR_H
#define UIMGR_H

#include "UIWindow.h"

class SYSCORE_API UIMgr : public Node {
public:
	//vtable 0h
	//(CoreNode: 4h-10h)
	//(Node: 14h-1Ch)
	Node m_unk1; // 20h

	UIMgr();
	~UIMgr();

	void RegisterGenWindowClass(LPCSTR lpszClass, void*, bool);
	void activateWindow(HWND, UIWindow* a3);
	bool isActive();
};

extern SYSCORE_API UIMgr* uiMgr;

#endif