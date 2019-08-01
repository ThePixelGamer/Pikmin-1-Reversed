#include "System.h"
#include <direct.h>

SYSCORE_API System* gsys;

System::System() : StdSystem() {
	gsys = this;

	char Dest[512];
	sprintf(Dest, "%s\\", getcwd(0, 0));
	this->currentWorkingDirectory = strdup(Dest);

}

System::System(const System& sys) : StdSystem(sys) {

}

System::~System() {

}

FileRandomAccessStream* System::openFile(char*, bool, bool)
{

	return new FileRandomAccessStream(0, 0);
}

void System::sndPlaySe(unsigned int) {

}

void System::beginRender() {

}

void System::buildModeList() {

}

UIWindow* System::createDebugStream(UIWindow*) {

	return new UIWindow;
}

FileRandomAccessStream* System::createFile(char* cwd, bool hasCwd) {
	char* workingDir;
	if (hasCwd)
		workingDir = this->currentWorkingDirectory;
	else
		workingDir = "";

	char Dest[256];
	sprintf(Dest, "%s", workingDir);

	char* fname;
	if (cwd)
		fname = this->fileName;
	else
		fname = "";

	sprintf(Dest, "%s%s", fname, cwd);

	FILE* fptr = fopen(Dest, "wb");
	if (!fptr)
		return 0;

	return new FileRandomAccessStream(fptr, cwd);
}

void System::doneRender() {

}

BaseApp* System::firstApp() {
	return new BaseApp;
}

void System::genAge(AgeServer*) {

}

struct AtxRouter* System::getAtxRouter() {
	return this->mainRouter;
}

int	System::getFrameCount() {
	return this->frameCount;
}

float System::getFrameRate() {
	return this->frameRate;
}

float System::getFrameTime() {
	return this->frameTime;
}

float System::getTime() {
	LARGE_INTEGER performanceCount;
	LARGE_INTEGER frequency;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&performanceCount);
	return performanceCount.QuadPart / frequency.QuadPart * 1000.0;
}

void System::halt(char* unused, int unused2, char* toPrint) {
	char Dest[2048];

	sprintf(Dest, "%s\n\nClick OK to quit now !", toPrint);
	MessageBoxA(0, Dest, "Error!", MB_ICONWARNING);
	exit(0);
}

void System::hardReset() {

}

int System::run(BaseApp*) {

	tagMSG message;

	while (1)
	{
		while (!PeekMessageA(&message, 0, 0, 0, 0))
		{
			if (gsys->isShutdown())
				PostQuitMessage(0);
			else
			{

			}
		}
		if (!GetMessageA(&message, 0, 0, 0))
			break;

		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return message.wParam;
}

/*void System::searchFiles(char*, char*, IDelegate2<char*, unsigned int>*, bool) {

}*/

void System::setAtxRouter(int) {

}

int System::setStreamType(int strTyp) {
	this->streamType = strTyp;
	return strTyp;
}

bool System::setVideoMode(bool a1, int a2, int a3, int a4) {
	OSVERSIONINFO versionInfo;

	versionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	if (!GetVersionExA(&versionInfo))
		MessageBox(NULL, "setVideoMode - GetVersionEx failed!!\n", " ", MB_OK);
	if (a1)
	{
		DEVMODEA dst;
		memset(&dst, 0, sizeof(OSVERSIONINFO));
		dst.dmSize = sizeof(OSVERSIONINFO);
		dst.dmPelsWidth = a2;
		dst.dmPelsHeight = a3;
		dst.dmBitsPerPel = a4;
		dst.dmFields = 0x1C0000;
		ChangeDisplaySettings(&dst, 4);
		// this is actually an if inside of a foor loop but it contains member variables and tbh cba doing the entire class
	}
	else
	{
		ChangeDisplaySettings(0, 0);
	}
	return 1;
}

void System::sleep(float) {

}

void System::updateSysClock() {

}

void System::waitRetrace() {

}
