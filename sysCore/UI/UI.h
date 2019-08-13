#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef UI_H
#define UI_H

#include "../sysCore.h"
#include<CommCtrl.h>
#pragma comment(lib, "comctl32.lib")

class SYSCORE_API RectArea {
public:
	int x1; //0h
	int y1; //4h
	int x2; //8h
	int y2; //Ch

	RectArea();
	RectArea(int, int, int, int);

	int height();
	int width();
	bool pointInside(int, int);
	void set(int, int, int, int);
};

class SYSCORE_API UIFrame : public Node {
public:
	//vtable 0h
	//(CoreNode: 4h-10h)
	//(Node: 14h-1Ch)
	RectArea m_frame; //20h
	RectArea m_zero; //30h
	RectArea m_client; //40h

	UIFrame();

	void calcClientFromFrame(RectArea&);
	void calcFrameFromClient(RectArea&);
	void setClient(RectArea&);
	void setFrame(RectArea&);
};

class SYSCORE_API UIWindow : public UIFrame {
public:
	//vtable 0h
	//(CoreNode: 4h-10h)
	//(Node: 14h-1Ch)
	//(UIFrame: 20h-40h)
	RectArea m_unk1; // 50h 
	UIWindow* m_parent; // 60h
	HWND m_hWnd; // 64h (sizeof(HANDLE) = void * = sizeof(int) = 4)
	int m_dwStyle; // 68h
	int m_dwExStyle; // 6Ch
	int m_unk6; // 70h
	int m_unk7; // 74h
	int m_unk8; // 78h
	int m_unk9; // 7Ch
	bool m_unk10; // 80h
	HMENU m_hMenu; // 84h (HMENU is a handle)

	UIWindow();
	UIWindow(UIWindow*, int, int, int, bool);
	~UIWindow();

	virtual void refreshWindow(); // 34h
	virtual void updateSizes(int, int); // 38h
	virtual void activate(); // 3Ch
	virtual int processMessage(HWND, unsigned int, WPARAM, long); // 40h
	virtual LRESULT returnMessage(HWND, unsigned int, WPARAM, long); // 44h
	virtual HDWP resizeChildren(HDWP, RectArea&); // 48h
	virtual HDWP resizeFrame(HDWP, RectArea&); // 4Ch
	virtual void createWindow(LPCSTR, LPCSTR, HMENU); // 50h
	virtual void dockTop(int, RectArea&, RectArea&); // 54h

	void closeChildren();
	void initFrame(UIWindow*, int, int, int, bool);
	void sizeWindow(int, int, int);
	void updateMove(int, int);
};

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