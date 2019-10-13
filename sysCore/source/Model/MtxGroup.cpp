#include <Model/MtxGroup.h>
#include <Object/DlobjInfo.h>
#include <System/System.h>

MtxGroup::MtxGroup() {}

void MtxGroup::exportData(RandomAccessStream&, unsigned __int32) {}

void MtxGroup::read(RandomAccessStream& stream)
{
    this->m_dependancyCount = stream.readInt();
    if (this->m_dependancyCount)
    {
        this->m_dependancies = new int[this->m_dependancyCount];
        for (int i = 0; i < this->m_dependancyCount; i++)
        {
            this->m_dependancies[i] = stream.readShort();
        }
    }

    this->m_dispListCount = stream.readInt();
    if (this->m_dispListCount)
    {
        this->m_dispLists = new DispList[this->m_dispListCount];
        for (int i = 0; i < this->m_dispListCount; i++)
        {
            this->m_dispLists[i].read(stream);
            DlobjInfo* obj = new DlobjInfo;
            obj->m_displayList = &this->m_dispLists[i];
            gsys->addGfxObject(obj);
        }
    }
}
