#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef CACHEINFO_H
#define CACHEINFO_H

#include <ID32.h>

class CacheInfo;

class SYSCORE_API AnimCacheInfo
{
public:
    // vtable - 0h
    void* unused1;        // 4h
    void* unused2;        // 8h
    void* unused3;        // Ch
    CacheInfo* cacheInfo; // 10h
    void* unk2;           // 14h
    void* unk3;           // 18h
    void* unk4;           // 1Ch
    // sizeof(AnimCacheInfo) must be 0x1C, (check operator=)

    AnimCacheInfo();

    void initData();
};

#endif