#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <io.h>
#include "resource.h"

#include "../sysCore/sysCore.h"
#include "../sysCore/System/System.h"
#include "../sysCore/Module.h"
#include "../sysCore/Stream/CmdStream.h"
#include "../sysCore/Stream/RamStream.h"

MenuPlugin* menuP = new MenuPlugin();
System unused;

void isLast() { menuP->prev = 0; } //may be autogen?

class UIMain : public UIWindow { //not an official name
public:
	UIMain() : UIWindow() {}
	UIMain(UIWindow* parent, int unk1, int dwStyle, int dwExStyle, bool unk2) : UIWindow(parent, unk1, dwStyle, dwExStyle, unk2) {}

	virtual int processMessage(HWND hWnd, unsigned int Msg, WPARAM wParam, long lParam) {
		if(Msg == WM_COMMAND) {
			for(MenuPlugin* i = menuP; i; i = i->next) {
				if(i->prev == wParam) {
					modMgr->Alloc(i->name);
					return UIWindow::processMessage(hWnd, Msg, wParam, lParam);
				}
			}
		}
		return UIWindow::processMessage(hWnd, Msg, wParam, lParam);
	}
}; 
UIMain* window;

void print(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	char dest[1024];

	if(sysCon) {
		if ("sysBootup")
			sysCon->print("%s: ", "sysBootup");
		vsprintf(dest, fmt, args);
		if(strlen(dest)) {
			sysCon->write(dest, strlen(dest));
		}
	}
}

void createUIWindow(HINSTANCE hInst) {
	window = new UIMain(0, 0, 0x16C40000, 0, true);
	window->setFrame(RectArea(690, 32, 1260, 300));
	window->createWindow("DUIClearWin\0", "OpenGL / Dolphin System", LoadMenu(sysHInst, MAKEINTRESOURCE(IDR_MENU1)));
	gsys->createDebugStream(window);
	window->refreshWindow();
	ShowWindow(window->m_hWnd, SW_SHOWNORMAL);
	print("Basedir = %s\n", gsys->baseDir);
}

void loadDLLsInDir(const char* dir) {
	_finddata_t fd_file;
	long dll;
	HMENU hSubMenu = 0;
	if(window) {
		HMENU hMenu = GetMenu(window->m_hWnd);
		if(hMenu)
			hSubMenu = GetSubMenu(hMenu, 0);
	}

	char dest[256];
	sprintf(dest, "%s/*.dll", dir);
	
	dll = _findfirst(dest, &fd_file);

	bool dll_count;
	char src[256];
	for(dll_count = (dll == -1); !dll_count; dll_count = (_findnext(dll, &fd_file) != 0)) {
		sprintf(src, "%s/%s", dir, fd_file.name);
		Module* temp = modMgr->loadModule(strdup(src));
		if(hSubMenu)
			temp->menuPlugins(menuP, hSubMenu);
	}
	
	_findclose(dll);
}

void passCmdParams(const char* str, char* unused) {
	loadDLLsInDir("plugins");

	if(strlen(str)) {
		print("got cmdParams [%d] : %s\n", strlen(str), str);
		CmdStream* cmd = new CmdStream(new RamStream(str, strlen(str)));

		while(!cmd->endOfCmds() && !cmd->endOfSection()) {
			cmd->getToken(true);
			if (cmd->isToken("+output")) {
				createUIWindow(sysHInst);
			} 
			else if(cmd->isToken("+plugins")) {
				char* tmp = cmd->getToken(true);
				loadDLLsInDir(tmp);
			} 
			else if(cmd->isToken("+direct")) {
				print("Creating atxDirectRouter\n");
				gsys->mainRouter = new AtxDirectRouter(cmd->getToken(true));
				print("done\n");
			}
			else if(cmd->isToken("+client")) {
				char* tmp = cmd->getToken(true);
				modMgr->Alloc(tmp);
			}
		}

		if(!cmd->endOfCmds()) 
			cmd->getToken(true);
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	sysHInst = hInstance;

	nodeMgr = new NodeMgr();
	modMgr  = new ModuleMgr();
	uiMgr   = new UIMgr();

	passCmdParams(lpCmdLine, "config.ini");

	if(!uiMgr->isActive() && !gsys->firstApp())
		MessageBoxA(NULL, "A top level window does not exist,\nthe application will now close.", "Warning!", MB_OK | MB_ICONWARNING);

    int ret = gsys->run(0);

	if(uiMgr)
		delete uiMgr;
	uiMgr = 0;

	if(modMgr)
		delete modMgr;
	modMgr = 0;

	if(nodeMgr)
		delete nodeMgr;
	nodeMgr = 0;

	return ret;
}