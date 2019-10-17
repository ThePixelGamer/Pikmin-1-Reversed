#include <Model/Joint.h>

Joint::Joint()
{
    this->m_unk2 = 1;
    this->dword10C = 0;
}

void Joint::read(RandomAccessStream& stream)
{
    this->m_index = stream.readInt();
    bool usingIdentifier = static_cast<bool>(stream.readInt());
    this->m_useVolume = (usingIdentifier & 1) != 0;
    this->m_useLightGroup = (usingIdentifier & 0x4000) != 0;

    this->m_bounds.m_minBounds.read(stream);
    this->m_bounds.m_maxBounds.read(stream);
    stream.readFloat();

    this->m_scale.read(stream);
    this->m_rotation.read(stream);
    this->m_translation.read(stream);

    this->m_matPolyCount = stream.readInt();
    for (int i = 0; i < m_matPolyCount; i++)
    {
        MatPoly* mPoly = new MatPoly();
        mPoly->m_index = static_cast<int>(stream.readShort());
        mPoly->m_dword20 = static_cast<int>(stream.readShort());
	}
}
