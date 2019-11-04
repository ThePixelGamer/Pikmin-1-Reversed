#include <Model/VtxMatrix.h>

void VtxMatrix::read(RandomAccessStream& stream)
{
    const short idx = stream.readShort();
    this->m_index = (this->m_partiallyWeighted = idx >= 0) ? idx : -idx - 1;
}

void VtxMatrix::write(RandomAccessStream& stream)
{
    // Basically an if statement
    this->m_partiallyWeighted ? stream.writeShort(this->m_index) : stream.writeShort(-(this->m_index + 1));
}