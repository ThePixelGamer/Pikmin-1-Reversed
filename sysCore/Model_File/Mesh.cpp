#include "Mesh.h"

Mesh::Mesh() {
  this->m_unk2 = 0;
  this->m_usingEmbossBump = -1;
  this->m_vcd = 1;
}

void Mesh::read(RandomAccessStream &stream) {
  this->m_usingEmbossBump = stream.readInt();
  this->m_vcd = stream.readInt();
  this->m_mtxGroupCount = stream.readInt();
  if (this->m_mtxGroupCount) {
    this->m_groups = new MtxGroup[this->m_mtxGroupCount];
    this->m_dependancyIdx = 0;
    for (int i = 0; i < this->m_mtxGroupCount; i++) {
      this->m_groups[i].read(stream);
      if (this->m_groups[i].m_dependancyCount > this->m_dependancyIdx)
        this->m_dependancyIdx = this->m_groups[i].m_dependancyCount;
    }
  }
}

void Mesh::exportData(RandomAccessStream &) {}
