#include <windows.h>
#include <string.h>
#include <stdio.h>
#include "..\sysCore\System\System.h"
#include "..\sysCore\sysCore.h"

MenuPlugin menuP; //0: wParam,  4: char* name, 8: MenuPlugin* (next one or something?)
System unused;

void isLast() { menuP.next = 0; } //may be autogen?

class UIMain : public UIWindow { //not an official name
public:
	UIMain(UIWindow* parent, int unk1, int dwStyle, int dwExStyle, bool unk2) : UIWindow(parent, unk1, dwStyle, dwExStyle, unk2) {}

	virtual int processMessage(HWND hWnd, unsigned int Msg, unsigned int wParam, long lParam) {
		if(Msg == WM_COMMAND)
			for(MenuPlugin* i = menuP; i; i = i->next) 
				if(i->wParam == wParam)
					modMgr->Alloc(i->name);

		return UIWindow::processMessage(hWnd, Msg, wParam, lParam);
	}
}; 
UIMain* window;

void print(const char* fmt, ...) {
	char* dest;
	va_list args;
	va_start(args, fmt);

	if(sysCon) {
		sysCon->print("%s: ", "sysBootup");
		vsprintf(dest, fmt, args);
		if(strlen(dest)) {
			sysCon->write(dest, strlen(dest));
		}
	}
} 

void createUIWindow(const char* str) {
	window = new UIMain();
	window->setFrame(new RectArea(690, 32, 1260, 300));
	window->createWindow("DUIClearWin", "OpenGL / Dolphin System", LoadMenuA(sysHInst, 101)); //load menu from resource file
	gsys->createDebugStream();
	window->refreshWindow();
	ShowWindow(window->m_hWnd, SW_SHOWNORMAL);
	print("Basedir = %s\n", gsys->baseDir);
}

void loadDLLsInDir(const char* dir) {
	HMENU hSubMenu;
	char* dest;
	char* src;
	_finddata_t fd_file;

	if(window) {
		HMENU hMenu = GetMenu(window->m_hWnd);
		if(hMenu)
			hSubMenu = GetSubMenu(hMenu, 0);
	}

	sprintf(dest, "%s/*.dll", dir);
	intptr_t dll = _findfirst(dest, &fd_file);

	for(bool dll_count = (dll == -1); !dll_count; dll_count = (_findnext(dll, &fd_file) != 0)) {
		sprintf(src, "%s/%s", dir, fd_file.name);
		if(hSubMenu)
			modMgr->loadModule(strdup(src))->menuPlugins(menuP, hSubMenu);
	}
	
	_findclose(fd_file);
}

size_t passCmdParams(const char* str) {
	loadDLLsInDir("plugins");
	size_t result = strlen(str); //seems to be unused, maybe for debugging purposes

	if(strlen(str)) {
		print("got cmdParams [%d] : %s\n", strlen(str), str);
		CmdStream* cmd = new CmdStream(new RamStream(str, strlen(str)));

		while(!cmd->endOfCmds() && !cmd->endOfSection()) {
			cmd->getToken(true);
			if (cmd->isToken("+output")) {
				createUIWindow(sysHInst);
			} 
			else if(cmd->isToken("+plugins")) {
				loadDLLsInDir(cmd->getToken(true));
			} 
			else if(cmd->isToken("+direct")) {
				print("Creating atxDirectRouter\n");
				gsys->mainRouter = new AtxDirectRouter(cmd->getToken(true));
				print("done\n");
			}
			else if (cmd->isToken("+client")) {
				modMgr->Alloc(cmd->getToken(true));
			}
		}

		result = cmd->endOfCmds();
		if(!result) 
			result = cmd->getToken(true);
	} 

	return result;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	sysHInst = hInstance;

	nodeMgr	  = new NodeMgr();
	moduleMgr = new ModuleMgr();
	uiMgr     = new UIMgr();
	
	passCmdParams(lpCmdLine);

	if(!uiMgr->isActive() && !gsys->firstApp())
		MessageBoxA(NULL, "A top level window does not exist,\nthe application will now close.", "Warning!", MB_OK | MB_ICONWARNING);

	int returnValue = gsys->run();

	delete nodeMgr;
	delete moduleMgr;
	delete uiMgr;

    return returnValue;
}