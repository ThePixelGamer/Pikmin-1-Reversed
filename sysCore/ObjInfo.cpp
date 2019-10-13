#include "ObjInfo.h"

//////////////////////////////////////////////////////////////////////
// GfxobjInfo class functions
//////////////////////////////////////////////////////////////////////

GfxobjInfo::GfxobjInfo() {
  this->next = 0;
  this->prev = 0;
  this->str = "";
  this->id32.setID('none');
  this->unused = 0;
}

void GfxobjInfo::attach() {}

void GfxobjInfo::detach() {}

void GfxobjInfo::insertAfter(GfxobjInfo *a2) {
  a2->next = this->next;
  a2->prev = this;
  this->next->prev = a2;
  this->next = a2;
}

void GfxobjInfo::remove() {
  this->next->prev = this->prev;
  this->prev->next = this->next;
}

//////////////////////////////////////////////////////////////////////
// AnmobjInfo class functions
//////////////////////////////////////////////////////////////////////

#include "AnimData.h"

AnmobjInfo::AnmobjInfo() { this->animData = 0; }

void AnmobjInfo::detach() { animData->detach(); }

//////////////////////////////////////////////////////////////////////
// TexobjInfo class functions
//////////////////////////////////////////////////////////////////////

#include "Texturing/Texture.h"

TexobjInfo::TexobjInfo() { this->texData = 0; }

void TexobjInfo::detach() { texData->detach(); }

#include "Model_File/DispList.h"

DlobjInfo::DlobjInfo() {
  this->m_displayList = 0;
  this->str = "displaylist";
  this->id32.setID('_gfx');
}

void DlobjInfo::detach() { this->m_displayList->m_unk3 = -1; }

void DlobjInfo::attach() {}