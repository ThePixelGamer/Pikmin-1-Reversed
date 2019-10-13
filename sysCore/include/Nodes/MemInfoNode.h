#pragma once

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef MEMINFONODE_H
#define MEMINFONODE_H

//
#include <Nodes/CoreNode.h>
//

class SYSCORE_API MemInfoNode : public CoreNode
{
public:
    MemInfoNode();
};

#endif