#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef STDSYSTEM_H
#define STDSYSTEM_H

#include <AgeServer.h>
#include <Ayu/AyuHeap.h>
#include <Nodes/Node.h>
#include <Object/GfxobjInfo.h>
#include <Stream/FileIO.h>
#include <Windows.h>

#include <algorithm>
#include <cstdarg>

class CacheTexture;
class LoadIdler;
class AnimData;
class Graphics;
class AyuHeap;
class LFInfo;
class Shape;
class LFlareGroup;
class Texture;

class SYSCORE_API StdSystem
{
public:
    // 0h - VTBL
    bool pending;         // 4h
    int dword8;           // 8h
    float initialFade;    // Ch
    float endFade;        // 10h
    void* m_consFont;     // 14h, class Font
    int m_frameClamp;     // 18h
    int dword1C;          // 1Ch
    int m_debugStreamUnk; // 20h
    int dword24;          // 24h
    int dword28;          // 28h
    int dword2C;          // 2Ch
    int dword30;          // 30h
    void* dword34;        // 34h
    void* dword38;        // 38h
    void* dword3C;        // 3Ch
    int matrixUnk;        // 40h
    Matrix4f* matrix;     // 44h
    char* bloRoot;        // 48h
    char* texRoot;        // 4Ch
    char* baseDir;        // 50h
    char* fileName;       // 54h
    AyuHeap heaps[8];     // 58h
    int heapNum;          // 198h
    int dword19C;         // 19Ch
    void* dword1A0;       // 1A0h
    void* dword1A4;       // 1A4h
    void* dword1A8;       // 1A8h
    void* dword1AC;       // 1ACh
    int m_lightCount;     // 1B0h
    void* dword1B4;       // 1B4h
    void* dword1B8;       // 1B8h
    void* dword1BC;       // 1BCh
    void* dword1C0;       // 1C0h
    void* dword1C4;       // 1C4h
    int unkShutdownCode;  // 1C8h
    void* dword1CC;       // 1CCh
    GfxobjInfo gfx;       // 1D0h
    bool m_toAttachObjs;  // 1F0h
    char* m_textureBase1; // 1F4h
    char* m_textureBase2; // 1F8h
    Shape* shape;         // 1FCh
    CoreNode core1;       // 200h
    CoreNode core2;       // 214h
    void* dword228;       // 228h
    void* m_lFlares;      // 22Ch
    void* dword230;       // 230h
    void* dword234;       // 234h
    void* dword238;       // 238h
    void* dword23C;       // 23Ch
    void* dword240;       // 240h


    StdSystem();

    virtual void initSoftReset();
    virtual RandomAccessStream* openFile(char*, bool, bool);
    virtual void copyRamToCache(unsigned int, unsigned int, unsigned int);
    virtual void copyCacheToRam(unsigned int, unsigned int, unsigned int);
    virtual void copyWaitUntilDone();
    virtual void copyCacheToTexture(CacheTexture*);
    virtual void Activate(bool);
    virtual void parseArchiveDirectory(char*, char*);
    virtual void sndPlaySe(unsigned int) {};
    virtual void startLoading(LoadIdler*, bool, unsigned int);
    virtual void endLoading();

    void Shutdown();
    void addAnimation(AnimData*, char*);
    void addGfxObject(GfxobjInfo*);
    void addTexture(Texture*, char*);
    void ageAnyAnimations(AgeServer& server, char* name);
    void attachObjs();
    void detachObjs();
    AnimData* findAnimation(char*);
    AnimData* findAnyAnimation(char*);
    GfxobjInfo* findAnyGfxObject(char*, unsigned int);
    int findAnyIndex(char*, char*);
    GfxobjInfo* findGfxObject(char*, unsigned __int32);
    AnimData* findIndexAnimation(char*, int);
    class TexobjInfo* findTexture(Texture*);
    void flushLFlares(Graphics*);
    void genAge(AgeServer&);
    void getAppMemory(char*);
    float getFade();
    float getHalfRand(float);
    AyuHeap* getHeap(int);
    int getHeapNum();
    // LFInfo* getLFlareInfo();
    double getRand(float);
    Shape* getShape(char*, char*, char*, bool);
    void initLFlares(int);
    void invalidateObjs(unsigned __int32, unsigned __int32);
    bool isActive();
    bool isShutdown();
    AnimData* loadAnimation(Shape*, char*, bool);
    void loadBundle(char*, bool);
    // Shape* loadShape(char*, bool);
    Texture* loadTexture(char*, bool);
    void onceInit();
    // LFlareGroup* registerLFlare(Texture*);
    void resetHeap(int, int);
    void resetLFlares();
    bool resetPending();
    void set2DRoot(char*, char*);
    void setActive(bool);
    void setDataRoot(char*);
    void setFade(float, float);
    void setFrameClamp(int);
    int setHeap(int);
    void setTextureBase(char*, char*);
    void softReset();
    static char* stringDup(char*);
};

#endif
