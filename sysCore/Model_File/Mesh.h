#pragma once

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef MESH_H
#define MESH_H

//
#include "../Nodes/CoreNode.h"
#include "../Stream/RandomAccessStream.h"
#include "MtxGroup.h"
//

class SYSCORE_API Mesh : public CoreNode {
public:
  // 14h - CoreNode
  int m_unk1;            // 14h
  int m_usingEmbossBump; // 18h
  int m_dependancyIdx;   // 1Ch
  int m_mtxGroupCount;   // 20h
  MtxGroup *m_groups;    // 24h
  int m_unk2;            // 28h
  int m_vcd;             // 2Ch

  Mesh();

  void read(RandomAccessStream &);
  void exportData(RandomAccessStream &);
};

#endif
