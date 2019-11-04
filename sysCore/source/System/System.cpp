#include <System/System.h>
#include <direct.h>

SYSCORE_API System* gsys;

void SYSTEMPRINT(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char dest[1024];

    if (sysCon)
    {
        if ("system")
            sysCon->print("%s: ", "system");
        vsprintf(dest, fmt, args);
        if (strlen(dest))
        {
            sysCon->write(dest, strlen(dest));
        }
    }
}

void SYSTEMHALT(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char dest[1024];
    vsprintf(dest, fmt, args);
    System::halt("c:\\development\\dolphinpiki\\syscore\\system.cpp", 21, dest);
    // file, line, error
}

System::System() : StdSystem() // DONE
{
    this->dword1C = 0;
    this->m_debugStreamUnk = true;
    this->dword24 = 0;
    this->dword28 = 1;
    this->dword2C = 1;
    this->streamType = 0;
    this->mainRouter = nullptr;
    sysCurrWnd = nullptr;
    this->m_textureByteUnk = false;
    this->m_unkGameAppBool = false;
    this->dword254 = 32;
    this->unkShutdownCode = 0x200000;
    this->heapNum = -1;
    gsys = this;
    this->m_unkGameAppBool2 = false;
    char Dest[512];
    sprintf(Dest, "%s\\", getcwd(0, 0));
    this->baseDir = strdup(Dest);
    this->m_heapSize = 0x5000000;
    this->m_heapMemory = GlobalAlloc(GMEM_FIXED, this->m_heapSize);
    this->heaps[0].init("sys", 1, this->m_heapMemory, this->m_heapSize);
    this->buildModeList();
    WSocket::init();
    gethostname(this->m_hostName, sizeof(this->m_hostName));
    this->onceInit();
    this->frameTime = 0.000099999997f;
}

System::System(const System& sys) : StdSystem(sys) {}

System::~System() {}

RandomAccessStream* System::openFile(char* cwd, bool hasCwd, bool print)
{
    char* _workingDir = (hasCwd ? this->baseDir : "");

    char fPath[256];
    sprintf(fPath, "%s", _workingDir);

    char* _fName = (hasCwd ? this->fileName : "");

    sprintf(fPath, "%s%s", _fName, cwd);

    FILE* fptr = fopen(fPath, "rb");
    if (!fptr)
        return 0;

    if (print)
        SYSTEMPRINT("Opened file %s\n", fPath);

    return new fileIO(fptr, cwd);
}

void System::beginRender() {}

void System::buildModeList() {}

UIWindow* System::createDebugStream(UIWindow* wind)
{
    DebugStream* strm = new DebugStream(wind);

    errCon = strm;
    sysCon = strm;
    return strm->m_window;
}

RandomAccessStream* System::createFile(char* cwd, bool hasCwd)
{
    char Dest[256];
    sprintf(Dest, "%s", (hasCwd ? this->baseDir : ""));

    /*combine current working directory with filename*/
    sprintf(Dest, "%s%s", (hasCwd ? "" : this->fileName), cwd);

    FILE* fptr = fopen(Dest, "wb");
    if (!fptr)
        return nullptr;

    return new fileIO(fptr, cwd);
}

void System::doneRender() {}

BaseApp* System::firstApp() { return static_cast<BaseApp*>(nodeMgr->firstNode()->Child()->Next()); }

void System::genAge(AgeServer& server)
{
    // this->pointerDword258->vfunc(server);
    StdSystem::genAge(server);
}

AtxRouter* System::getAtxRouter() { return this->mainRouter; }

int System::getFrameCount() { return this->frameCount; }

float System::getFrameRate() { return this->frameRate; }

float System::getFrameTime() { return this->frameTime; }

float System::getTime()
{
    LARGE_INTEGER performanceCount;
    LARGE_INTEGER frequency;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&performanceCount);
    return performanceCount.QuadPart / frequency.QuadPart * 1000.0;
}

void System::halt(char* unused, int unused2, char* toPrint)
{
    char Dest[2048];

    sprintf(Dest, "%s\n\nClick OK to quit now !", toPrint);
    MessageBoxA(0, Dest, "Error!", MB_ICONWARNING);
    exit(0);
}

void System::hardReset()
{
    // this->m_consFont = new Font;
    // this->m_consFont->setTexture(this->loadTexture("constFont.bti", true), 16, 8);
    gsys->set2DRoot("screen/eng_blo/", "screen/eng_tex/");
    this->frameCount = 0;
}

int System::run(BaseApp*)
{
    tagMSG message;

    while (1)
    {
        while (!PeekMessageA(&message, 0, 0, 0, 0))
        {
            if (!uiMgr->isActive() && !this->firstApp())
            {
                SYSTEMPRINT("shutting down because no toplevel windows");
                gsys->Shutdown();
            }
            if (gsys->isShutdown())
                PostQuitMessage(0);
            else
            {
                this->updateSysClock();
                this->controllermgr.update();
            }
        }
        if (!GetMessageA(&message, 0, 0, 0))
            break;

        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    return message.wParam;
}

#include <io.h>
#include <time.h>

void System::searchFiles(char* base, char* type, IDelegate2<char*, unsigned int>* delegate, bool unk1) // TODO
{
    char dest[256];
    sprintf(dest, "%s/%s", base, type);
    SYSTEMPRINT("base = %s : type = %s\n", base, type);

    struct _finddata_t fblock;
    int handle = _findfirst(dest, &fblock);
    for (int i = (handle == -1); !i; i = (_findnext(handle, &fblock) != 0))
    {
        if (fblock.attrib & _A_SUBDIR)
        {
            char t[0x10];
            sprintf(t, "%s/%s", base, fblock.name);
            delegate->invoke(t, fblock.size);
        }
    }
}

void System::setAtxRouter(AtxRouter* r) { this->mainRouter = r; }

int System::setStreamType(int strTyp)
{
    this->streamType = strTyp;
    return strTyp;
}

bool System::setVideoMode(bool a1, int width, int height, int bits)
{
    OSVERSIONINFO versionInfo;

    versionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    if (!GetVersionEx(&versionInfo))
        SYSTEMHALT("setVideoMode - GetVersionEx failed!!\n");
    if (a1)
    {
        DEVMODEA dst;
        memset(&dst, 0, sizeof(OSVERSIONINFO));
        dst.dmSize = sizeof(OSVERSIONINFO);
        dst.dmPelsWidth = width;
        dst.dmPelsHeight = height;
        dst.dmBitsPerPel = bits;
        dst.dmFields = 0x1C0000;
        ChangeDisplaySettings(&dst, 4);
        // this is actually an if inside of a foor loop but it contains member
        // variables and tbh cba doing the entire class
    }
    else
    {
        ChangeDisplaySettings(0, 0);
    }
    return true;
}

void System::sleep(float toSleep) { SleepEx((toSleep * 1000.0), true); }

void System::updateSysClock() {}

void System::waitRetrace() {}
