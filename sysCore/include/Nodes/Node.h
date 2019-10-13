#pragma once

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef NODE_H
#define NODE_H

//
#include <Math/Matrix4f.h>
#include <Math/SRT.h>
#include <Nodes/CoreNode.h>
//

class Graphics;
class Matrix4f;
class SRT;
class VQS; // never made /shrug

class SYSCORE_API Node : public CoreNode
{
public:
    // vtable 0h
    //(CoreNode: 4h-10h)
    int type;    // 14h
    int flags;   // 18h
    int dword1c; // 1Ch

    Node(char* = "<Node>");

    //(CoreNode: 0 - 16)
    virtual void update();              // this+20
    virtual void draw(Graphics&);       // this+24
    virtual void render(Graphics&);     // this+28
    virtual void concat();              // this+44
    virtual void concat(VQS&);          // this+40
    virtual void concat(SRT&);          // this+36
    virtual void concat(Matrix4f&);     // this+32
    virtual Matrix4f* getModelMatrix(); // this+48

    void clearFlag(int);
    int getFlag(int);
    int getFlags();
    int getType();
    void init(char*);
    void setFlag(int);
    void setFlag(int, bool);
    void setFlags(int);
    void setType(int);
    void togFlag(int);
};

#endif