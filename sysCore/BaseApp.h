#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef BASEAPP_H
#define BASEAPP_H

#include "AgeServer.h"
#include "Atx/AtxCommandStream.h"
#include "Nodes/Node.h"

class SYSCORE_API BaseApp : public Node {
public:
  // baseapp member variables (base class = node)
  // 0h - vtbl ptr
  AtxCommandStream *m_cmdStream; // 20h
  AgeServer *m_server;           // 24h
  bool m_unkByte;                // 28h
  int m_unkInt;                  // 2Ch
  Node m_node1;                  // 30h
  int heapType;                  // 50h

  BaseApp();

  virtual void genAge(AgeServer &);

  void startAgeServer();
  void stopAgeServer();
};

#endif
