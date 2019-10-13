#include <Model/DispList.h>
#include <Object/DlobjInfo.h>

DlobjInfo::DlobjInfo()
{
    this->m_displayList = 0;
    this->str = "displaylist";
    this->id32.setID('_gfx');
}

void DlobjInfo::detach() { this->m_displayList->m_unk3 = -1; }

void DlobjInfo::attach() {}
