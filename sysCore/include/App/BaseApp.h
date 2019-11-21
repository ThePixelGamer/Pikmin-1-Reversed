#pragma once

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef BASEAPP_H
#define BASEAPP_H

#include <AgeServer.h>
#include <Atx/AtxCommandStream.h>
#include <Nodes/Node.h>

/*
 *  Base class, used for inheritance.
 */
class SYSCORE_API BaseApp : public Node
{
public:
    // 0h - vtbl ptr
    // 1Ch -  Node
    AtxCommandStream* m_cmdStream; // 20h
    AgeServer* m_server;           // 24h
    bool m_unkByte;                // 28h
    int m_unkInt;                  // 2Ch
    Node m_node1;                  // 30h
    int heapType;                  // 50h

    BaseApp();
    virtual ~BaseApp();

    virtual void genAge(AgeServer&);
    virtual void InitApp(char*) {}
    virtual bool idle() { return false; }
    virtual bool keyDown(int, int, int) { return false; }
    virtual void softReset();
    virtual void useHeap(int);
    virtual void procCmd(char*) {}

    bool idleUpdate();
    void startAgeServer();
    void stopAgeServer();

    double rnd();
    double rnd(float);
};

#endif
