#pragma once

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef DISPLIST_H
#define DISPLIST_H

//
#include <Nodes/CoreNode.h>
#include <Nodes/FaceNode.h>
#include <sysCore.h>
//

class SYSCORE_API DispList : public CoreNode
{
public:
    int m_unk1;          // 14h
    int m_dispDataCount; // 18h
    uchar* m_dispData;   // 1Ch
    int m_unk3;          // 20h
    int m_unk4;          // 24h
    int m_unk5;          // 28h
    FaceNode m_face;     // 2Ch

    DispList();
    DispList(int);

    void exportData(RandomAccessStream&, unsigned __int32);
    void outputTriData(RandomAccessStream&, unsigned __int32, bool);
    // void prepareTriList(TriStripifier);
    void read(RandomAccessStream&);
};

#endif
