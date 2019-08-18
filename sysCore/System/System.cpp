#include "System.h"
#include <direct.h>

SYSCORE_API System* gsys;

void SYSTEMPRINT(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	char dest[1024];

	if(sysCon) {
		if ("system")
			sysCon->print("%s: ", "system");
		vsprintf(dest, fmt, args);
		if(strlen(dest)) {
			sysCon->write(dest, strlen(dest));
		}
	}
}

void SYSTEMHALT(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	char dest[1024];
	vsprintf(dest, fmt, args);
	System::halt("c:\\development\\dolphinpiki\\syscore\\system.cpp", 21, dest);
	// file, line, error
}

System::System() : StdSystem() {
	gsys = this;

	char Dest[512];
	sprintf(Dest, "%s\\", getcwd(0, 0));
	this->baseDir = strdup(Dest);

}

System::System(const System& sys) : StdSystem(sys) {

}

System::~System() {

}

RandomAccessStream* System::openFile(char* cwd, bool hasCwd)
{
	char* _workingDir;
	if (hasCwd)
		_workingDir = this->baseDir;
	else
		_workingDir = "";

	char fPath[256];
	sprintf(fPath, "%s", _workingDir);

	char* _fName = (hasCwd ? this->fileName : "");

	sprintf(fPath, "%s%s", _fName, cwd);

	FILE* fptr = fopen(fPath, "wb");
	if (!fptr)
		return 0;

	return new FileRandomAccessStream(fptr, cwd);
}

void System::sndPlaySe(unsigned int) {

}

void System::beginRender() {

}

void System::buildModeList() {

}

UIWindow* System::createDebugStream(UIWindow* wind) {
	DebugStream* strm = new DebugStream(wind);

	errCon = strm;
	sysCon = strm;
	return strm->m_window;
}

RandomAccessStream* System::createFile(char* cwd, bool hasCwd) {
	char* workingDir;
	if (hasCwd)
		workingDir = this->baseDir;
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
	return dynamic_cast<BaseApp*>(nodeMgr->firstNode()->Child()->Next());
}

void System::genAge(AgeServer*) {

}

AtxRouter* System::getAtxRouter() {
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
			if (!uiMgr->isActive() && !this->firstApp()) {
				SYSTEMPRINT("shutting down because no toplevel windows");
				gsys->Shutdown();
			}
			if (gsys->isShutdown())
				PostQuitMessage(0);
			else
			{
				this->updateSysClock();
				//this->controllerMgr->update();
			}
		}
		if (!GetMessageA(&message, 0, 0, 0))
			break;

		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return message.wParam;
}

/*void System::searchFiles(char* base, char* type, IDelegate2<char*, unsigned int>*, bool) {

}*/

void System::setAtxRouter(int) {

}

int System::setStreamType(int strTyp) {
	this->streamType = strTyp;
	return strTyp;
}

bool System::setVideoMode(bool a1, int width, int height, int bits) {
	OSVERSIONINFO versionInfo;

	versionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	if (!GetVersionEx(&versionInfo))
		SYSTEMHALT("setVideoMode - GetVersionEx failed!!\n");
	if (a1) {
		DEVMODEA dst;
		memset(&dst, 0, sizeof(OSVERSIONINFO));
		dst.dmSize = sizeof(OSVERSIONINFO);
		dst.dmPelsWidth = width;
		dst.dmPelsHeight = height;
		dst.dmBitsPerPel = bits;
		dst.dmFields = 0x1C0000;
		ChangeDisplaySettings(&dst, 4);
		// this is actually an if inside of a foor loop but it contains member variables and tbh cba doing the entire class
	}
	else {
		ChangeDisplaySettings(0, 0);
	}
	return true;
}

void System::sleep(float toSleep) {
	SleepEx( (toSleep * 1000.0) , true);
}

void System::updateSysClock() {

}

void System::waitRetrace() {

}
