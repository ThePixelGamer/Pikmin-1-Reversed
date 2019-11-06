#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef SYSTEM_H
#define SYSTEM_H

#include <App/BaseApp.h>
#include <Atx/AtxFileStream.h>
#include <Atx/AtxRouter.h>
#include <Controller/ControllerManager.h>
#include <IDelegate.h>
#include <Networking/WSocket.h>
#include <Stream/BufferedStream.h>
#include <Stream/DebugStream.h>
#include <System/StdSystem.h>
#include <UI/UIMgr.h>

class SYSCORE_API System : public StdSystem
{
public:
    //(StdSystem: 4h-240h)
    void* dword244;
    void* dword248;
    bool m_textureByteUnk;  // 24Ch
    bool m_unkGameAppBool;  // 24Dh
    bool m_unkGameAppBool2; // 24Eh
    void* dword250;
    int dword254;
    void* dword258; // 258h
    void* m_heapMemory;
    int m_heapSize; // 260h
    AtxFileStream atxfilestream264;
    BufferedStream bufferedStream;
    int streamType;
    ControllerMgr controllermgr;
    char m_hostName[0x80];       // 3B8h
    class AtxRouter* mainRouter; // 438h
    void* dword43C;
    void* dword440;
    void* dword444;
    void* dword448;
    void* dword44C;
    void* dword450;
    void* dword454;
    float frameTime; // 458h
    float frameRate; // 45Ch
    void* dword460;
    void* dword464;
    int frameCount; // 468h

    System();
    System(const System&);
    ~System();

    virtual RandomAccessStream* openFile(char*, bool, bool);
    // virtual void 			parseArchiveDirectory(char * );
    virtual void sndPlaySe(unsigned __int32) { }

    void beginRender();
    void buildModeList();
    UIWindow* createDebugStream(UIWindow*);
    RandomAccessStream* createFile(char*, bool);
    void doneRender();
    BaseApp* firstApp();

    virtual void genAge(AgeServer&);
    AtxRouter* getAtxRouter();
    int getFrameCount();
    float getFrameRate();
    float getFrameTime();
    float getTime();
    static void halt(char*, int, char*);
    void hardReset();
    int run(BaseApp*);
    void searchFiles(char*, char*, IDelegate2<char*, unsigned int>*, bool);
    void setAtxRouter(AtxRouter*);
    int setStreamType(int);
    bool setVideoMode(bool, int, int, int);
    void sleep(float);
    void updateSysClock();
    void waitRetrace();
};

extern SYSCORE_API System* gsys;
#endif
