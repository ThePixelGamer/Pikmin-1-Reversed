#pragma once

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef CORENODE_H
#define CORENODE_H

//
#include <Nodes/ANode.h>
#include <Stream/RandomAccessStream.h>
//

class SYSCORE_API CoreNode : public ANode
{
public:
    // vtable 0h
    char* name;       // 4h
    CoreNode* parent; // 8h
    CoreNode* next;   // Ch
    CoreNode* child;  // 10h

    CoreNode(char* = "CoreNode");

    virtual void genAge(AgeServer&);           // this+0 TODO
    virtual void genAgeNode(AgeServer&);       // this+4 TODO
    virtual int getAgeNodeType();              // this+8
    virtual void write(RandomAccessStream&) {} // this+12
    virtual void read(RandomAccessStream&) {}  // this+16

    CoreNode* Next();
    void Next(CoreNode*);
    CoreNode* Child();
    void Child(CoreNode*);
    char* Name();
    CoreNode* Parent();

    int getChildCount();

    void initCore(char*);
    void setName(char*);
    char* getName();

    void add(CoreNode*);
    void del();

    void load(char*, char*, unsigned __int32); // TODO

    void genWrite(AgeServer&) {} // TODO
    void genRead(AgeServer&);    // TODO
};

#endif
