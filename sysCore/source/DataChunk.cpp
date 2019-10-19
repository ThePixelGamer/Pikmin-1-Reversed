#include <DataChunk.h>
#include <Stream/CmdStream.h>
#include <Stream/RandomAccessStream.h>
#include <sysCore.h>

DataChunk::DataChunk()
{
    this->m_dataIndex = 0;
    this->m_dataSize = 0;
    this->m_data = nullptr;
}

void DataChunk::addData(float toAdd)
{
    // Check for overflow
    if (this->m_dataIndex >= this->m_dataSize)
    {
        // Add to the size so overflow shouldn't easily happen again
        this->m_dataSize = this->m_dataIndex + 0x800;
        // Create a new temporary data arary
        float* data = new float[this->m_dataSize];
        // If data index wasn't at 0, it was somewhere along the array
        if (this->m_dataIndex)
            // So then because it was somewhere along the array, copy the data over to the new array
            memcpy(data, this->m_data, sizeof(m_data) * this->m_dataIndex);
        // Would overflow, delete the data
        delete this->m_data;
        // Copy new array to m_data
        this->m_data = data;
    }
    this->m_data[this->m_dataIndex++] = toAdd;
}

void DataChunk::getData(CmdStream* stream)
{
    stream->getToken(true);
    int iterator = 0;
    while (stream->endOfCmds() == false && stream->endOfSection() == false)
    {
        if ((iterator & 7) == false)
        {
            stream->getToken(true);
            if (stream->isToken("size"))
            {
                int newDataSize;
                sscanf(stream->getToken(true), "%d", &newDataSize);
                this->setDataSize(newDataSize);
                stream->getToken(true);
            }
        }
        float data;
        sscanf(stream->getToken(true), "%f", &data);
        this->addData(data);
        iterator++;
    }
    if (stream->endOfCmds() == false)
        stream->getToken(true);
}

void DataChunk::read(RandomAccessStream& stream)
{
    int dataSize = stream.readInt();
    this->setDataSize(dataSize);
    for (int i = 0; i < dataSize; i++)
    {
        this->m_data[i] = stream.readFloat();
    }
}

void DataChunk::write(RandomAccessStream& stream)
{
    stream.writeInt(this->m_dataIndex);
    for (int i = 0; i < m_dataIndex; i++)
        stream.writeFloat(this->m_data[i]);
}

void DataChunk::setDataSize(int dataSize)
{
    this->m_data = new float[dataSize];
    this->m_dataSize = dataSize;
}
