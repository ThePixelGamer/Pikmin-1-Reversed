#include <Object/GfxobjInfo.h>

GfxobjInfo::GfxobjInfo()
{
    this->next = 0;
    this->prev = 0;
    this->str = "";
    this->id32.setID('none');
    this->unused = 0;
}

void GfxobjInfo::attach() {}

void GfxobjInfo::detach() {}

void GfxobjInfo::insertAfter(GfxobjInfo* a2)
{
    a2->next = this->next;
    a2->prev = this;
    this->next->prev = a2;
    this->next = a2;
}

void GfxobjInfo::remove()
{
    this->next->prev = this->prev;
    this->prev->next = this->next;
}