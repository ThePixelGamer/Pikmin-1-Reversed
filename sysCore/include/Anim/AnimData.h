#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef ANIMDATA_H
#define ANIMDATA_H

#include <DataChunk.h>
#include <Nodes/CoreNode.h>
#include <Nodes/SRTNode.h>

class AnimDataInfo;
class AnimCacheInfo;

class SYSCORE_API AnimData : public CoreNode
{
public:
    // vtable 0h
    //(CoreNode: 4h-10h)
    DataChunk* m_scaling;     // _14
    DataChunk* m_rotation;    // _18
    DataChunk* m_translation; // _1C
    AnimData* dword20;        // _20
    int dword24;              // _24
    int m_jointCount;         // _28
    int dword2C;              // _2C
    int m_frameCount;         // 30h
    int dword34;              // _34
    int dword38;              // _38
    int dword3C;              // _3C
    AnimCacheInfo* animCache; // 40h

    AnimData();
    AnimData(char* name);

    virtual void genAge(AgeServer&);
    virtual void extractSRT(SRT&, int, AnimDataInfo*, float);
    virtual void makeAnimSRT(int, Matrix4f*, Matrix4f*, AnimDataInfo*, float);
    virtual void detach();
    virtual void writeType(RandomAccessStream&);

    void initData();
    void delAnim(AgeServer&);
    void playAnim(AgeServer&);
};

#endif
