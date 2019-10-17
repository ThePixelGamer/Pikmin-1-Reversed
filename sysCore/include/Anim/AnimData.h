#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef ANIMDATA_H
#define ANIMDATA_H

#include <Nodes/CoreNode.h>
#include <Nodes/SRTNode.h>

class AnimDataInfo;
class AnimCacheInfo;

class SYSCORE_API AnimData : public CoreNode
{
public:
    // vtable 0h
    //(CoreNode: 4h-10h)
    int m_frameCount;         // 30h
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
