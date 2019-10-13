#include "DispList.h"

DispList::DispList() {
  this->m_face.initCore("");
  this->m_unk4 = 0;
  this->m_unk5 = 0;
  this->m_unk1 = 0;
  this->m_unk3 = -1;
}

DispList::DispList(int unk) {
  this->m_face.initCore("");
  this->m_unk4 = 0;
  this->m_unk5 = 0;
  this->m_unk1 = unk & 3;
  this->m_unk3 = -1;
}

void DispList::exportData(RandomAccessStream &, unsigned __int32) {}

void DispList::outputTriData(RandomAccessStream &, unsigned __int32, bool) {}

void DispList::read(RandomAccessStream &stream) {
  this->m_unk1 = stream.readInt();
  this->m_unk5 = stream.readInt();
  this->m_dispDataCount = stream.readInt();
  stream.skipPadding(0x20);
  this->m_dispData = new (32) uchar[this->m_dispDataCount];
  stream.read(this->m_dispData, this->m_dispDataCount);
}
