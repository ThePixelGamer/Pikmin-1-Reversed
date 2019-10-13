#pragma once

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef EDITNODE_H
#define EDITNODE_H

//
#include <Graphics/Graphics.h>
#include <Nodes/CoreNode.h>
//

class DataMsg;

class SYSCORE_API EditNode : public CoreNode
{
public:
    EditNode(char*);

    virtual void msgCommand(DataMsg&);
    virtual void render2d(Graphics&, int&);
};

#endif