#include <AgeServer.h>
#include <Anim/AnimData.h>
#include <CacheInfo.h>
#include <IDelegate.h>

AnimData::AnimData() {}

void AnimData::genAge(AgeServer& server)
{
    server.StartGroup(this->Name());

    IDelegate1<AgeServer&>* playButton =
        new Callback1<AnimData*, void (AnimData::*)(AgeServer&), AgeServer&>(this, &AnimData::playAnim);
    server.NewButton("play/pause Anim", playButton, 222);
    if (strcmp(this->name, "Null Anim"))
    {
        IDelegate1<AgeServer&>* deleteButton =
            new Callback1<AnimData*, void (AnimData::*)(AgeServer&), AgeServer&>(this, &AnimData::delAnim);
        server.NewButton("play/pause Anim", deleteButton, 222);
    }
    // server.NewEditor("Frame", this->);
    server.EndGroup();
}

void AnimData::extractSRT(SRT&, int, AnimDataInfo*, float) {}

void AnimData::makeAnimSRT(int, Matrix4f*, Matrix4f*, AnimDataInfo*, float) {}

void AnimData::detach() {}

void AnimData::writeType(RandomAccessStream&) {}

void AnimData::delAnim(AgeServer&) {}

void AnimData::playAnim(AgeServer&) {}

void AnimData::initData()
{
    int size = this->m_frameCount;
    animCache = new AnimCacheInfo[size];
}
