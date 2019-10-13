#pragma once

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef FACENODE_H
#define FACENODE_H

//
#include <Nodes/CoreNode.h>
//

class SYSCORE_API FaceNode : public CoreNode
{
public:
    int m_facenode_0;  // 14h
    int m_facenode_1;  // 18h
    int m_facenode_2;  // 1Ch
    int m_facenode_3;  // 20h
    int m_facenode_4;  // 24h
    int m_facenode_5;  // 28h
    int m_facenode_6;  // 2Ch
    int m_facenode_7;  // 30h
    int m_facenode_8;  // 34h
    int m_facenode_9;  // 38h
    int m_facenode_10; // 3Ch
    int m_facenode_11; // 40h
    int m_facenode_12; // 44h

    FaceNode();
    FaceNode(int);
};

#endif