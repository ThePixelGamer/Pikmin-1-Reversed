#pragma once

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef MTXGROUP_H
#define MTXGROUP_H

//
#include <Model/DispList.h>
#include <Stream/RandomAccessStream.h>
//

/*
 *  Stands for Matrix Group, contains display lists from models.
 */
class SYSCORE_API MtxGroup
{
public:
    int m_dependancyCount; // 0h
    int* m_dependancies;   // 4h
    int m_dispListCount;   // 8h
    DispList* m_dispLists; // Ch

    MtxGroup();

    void exportData(RandomAccessStream&, unsigned __int32);
    void read(RandomAccessStream&);
};

#endif
