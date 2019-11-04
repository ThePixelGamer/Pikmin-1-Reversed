#include <Model/VtxMatrix.h>

void VtxMatrix::read(RandomAccessStream& stream)
{
    const short idx = stream.readShort();
    this->m_partiallyWeighted = idx >= 0;
    if (this->m_partiallyWeighted)
        this->m_index = idx;
    else
        this->m_index = -idx - 1;
}

void VtxMatrix::write(RandomAccessStream& stream)
{
    if (this->m_partiallyWeighted)
    {
        stream.writeShort(this->m_index);
    }
    else
    {
        stream.writeShort(-(this->m_index + 1));
    }
}