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
	RectArea(int x1, int y1, int x2, int y2);

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

class SYSCORE_API ToolWindow : public UIWindow {
public:
	UIWindow* m_toolWindow; // 88h
	HINSTANCE m_unk11; // 8Ch

	ToolWindow(UIWindow*, int, int, int, bool);

	void initTools(HINSTANCE, int, TBBUTTON*, tagTBADDBITMAP*);
	virtual int processMessage(HWND, unsigned int, WPARAM, long); // todo: find out class type 
	virtual void createWindow(LPCSTR className, LPCSTR windowName, HMENU hMenu);

};

//////////////////////////////////////////////////////////////////////
// UI 'box classes
//////////////////////////////////////////////////////////////////////
static char cBoxStringBuf[256];

class SYSCORE_API ComboBox : public UIWindow {
public:
	//vtable 0h
	//(CoreNode: 4h-10h)
	//(Node: 14h-1Ch)
	//(UIFrame: 20h-40h)
	//(UIWindow: 50h-84h)
	UIWindow* m_boxWindow; //88h
	int m_boxExStyle; //8Ch

	ComboBox(UIWindow*, int, int, int, bool);
	// destructor gets auto-gen'd

	void addOption(char*, bool);
	void selOption(int);

	virtual int processMessage(HWND, unsigned int, WPARAM, long);
	virtual void createWindow(LPCSTR, LPCSTR, HMENU);
	virtual void entryHandler(char*); //58h
};

static char eBoxStringBuf[256];

class SYSCORE_API EditBox : public ComboBox {
public:
	//vtable 0h
	//(CoreNode: 4h-10h)
	//(Node: 14h-1Ch)
	//(UIFrame: 20h-40h)
	//(UIWindow: 50h-84h)
	//(ComboBox: 88h-8Ch)

	EditBox(UIWindow*, int, int, int, bool);

	virtual void entryHandler(char* msg);
	virtual int processMessage(HWND, unsigned int, WPARAM, long);
};

class SYSCORE_API OptionBox : public ComboBox {
public:
	//vtable 0h
	//(CoreNode: 4h-10h)
	//(Node: 14h-1Ch)
	//(UIFrame: 20h-40h)
	//(UIWindow: 50h-84h)
	//(ComboBox: 88h-8Ch)

	OptionBox(UIWindow*, int, int, int, bool);

	virtual void selectionChanged(int);
	virtual int processMessage(HWND, unsigned int, WPARAM, long);
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