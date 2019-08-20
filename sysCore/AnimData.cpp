#include "AnimData.h"

#include "AnimCacheInfo.h"

AnimData::AnimData() {

}

void AnimData::genAge(AgeServer*) {

}

void AnimData::extractSRT(SRT*, int, AnimDataInfo*, float) {

}

void AnimData::makeAnimSRT(int, Matrix4f*, Matrix4f*, AnimDataInfo*, float) {

}

void AnimData::detach() {
    int size = animCacheSize;
    animCache = new AnimCacheInfo[size];
}

void AnimData::writeType(RandomAccessStream*) {

}
