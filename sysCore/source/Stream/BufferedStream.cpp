#include <Stream/BufferedStream.h>
#include <System/System.h>

BufferedInputStream::BufferedInputStream()
{
    this->m_buffer = nullptr;
    this->m_bufferStream = nullptr;
}

BufferedInputStream::BufferedInputStream(Stream* stream, unsigned __int8* buf, int bufSize)
{
    this->init(stream, buf, bufSize);
}

void BufferedInputStream::read(void* _buffer, int _size)
{
    char* buffer = static_cast<char*>(_buffer);
    while (_size)
    {
        this->fillBuffer();
        int size = _size;
        if (size > this->m_amountToRead - this->m_readLimit)
            size = this->m_amountToRead - this->m_readLimit;
        memcpy(buffer, &this->m_buffer[this->m_readLimit], size);
        buffer += size;
        this->m_readLimit += size;
        this->m_position += size;
        _size -= size;
    }
}

int BufferedInputStream::getPending() { return this->m_bufferStream->getPending() - this->m_position; }

void BufferedInputStream::close() { this->m_bufferStream->close(); }

void BufferedInputStream::fillBuffer()
{
    if (this->m_amountToRead == this->m_readLimit)
    {
        this->m_amountToRead = this->getPending();
        if (this->m_amountToRead > this->m_bufferSize)
            this->m_amountToRead = this->m_bufferSize;
        this->m_bufferStream->read(this->m_buffer, this->m_amountToRead);
        this->m_readLimit = 0;
    }
}

int BufferedInputStream::getPosition() { return this->m_position; }

void BufferedInputStream::init(Stream* stream, unsigned __int8* buf, int bufSize)
{
    this->filePath = StdSystem::stringDup(stream->filePath);
    this->m_bufferSize = bufSize;
    uchar* buffer = (!buf) ? buf = new (32) uchar[this->m_bufferSize] : buf;
    this->m_buffer = buffer;
    this->m_position = 0;
    this->m_readLimit = 0;
    this->m_amountToRead = 0;
    this->m_bufferStream = stream;
    this->fillBuffer();
}

void BufferedInputStream::open(Stream* stream)
{
    this->m_readLimit = 0;
    this->m_position = 0;
    this->m_amountToRead = 0;
    this->m_bufferStream = stream;
}

void BufferedInputStream::resetBuffer()
{
    this->m_readLimit = 0;
    this->m_amountToRead = 0;
}

BufferedOutputStream::BufferedOutputStream(Stream* stream, int bufferSize, bool unk)
{
    this->m_bufferStream = stream;
    this->m_bufferPosition = 0;
    this->m_buffer = new uchar[bufferSize];
    this->m_unk = unk;
    this->m_bufferSize = bufferSize - 1;
}

void BufferedOutputStream::write(void* buffer, int size)
{
    if (this->m_unk)
    {
        for (int i = 0; i < size; i++)
        {
            char toAdd = static_cast<char*>(buffer)[i];
            this->addChar(toAdd);
            if (toAdd == '\n')
                this->flush();
        }
    }
    else
    {
        for (int i = 0; i < size; i++)
            this->addChar(static_cast<char*>(buffer)[i]);
    }
}

void BufferedOutputStream::flush()
{
    // Null out the current byte
    this->m_buffer[this->m_bufferPosition] = 0;
    this->m_bufferStream->write(this->m_buffer, this->m_bufferPosition);
    this->m_bufferPosition = 0;
}

void BufferedOutputStream::addChar(char toAdd)
{
    this->m_bufferPosition++;
    this->m_buffer[this->m_bufferPosition] = toAdd;
    if (this->m_bufferPosition >= this->m_bufferSize)
        this->flush();
}

BufferedStream::BufferedStream(RandomAccessStream* stream, int bufferSize) : m_buffStream(stream, 0, bufferSize)
{
    this->filePath = stream->filePath;
    this->m_stream = stream;
}

BufferedStream::BufferedStream() {}

void BufferedStream::read(void* buffer, int size) { this->m_stream->read(buffer, size); }

int BufferedStream::getPending() { return this->m_buffStream.getPending(); }

void BufferedStream::close() { this->m_stream->close(); }

int BufferedStream::getPosition()
{
    return this->getPending() - (this->m_buffStream.m_amountToRead - this->m_buffStream.m_readLimit);
}

void BufferedStream::setPosition(int pos)
{
    this->m_buffStream.resetBuffer();
    this->m_stream->setPosition(pos);
}

int BufferedStream::getLength() { return this->m_stream->getLength(); }

void BufferedStream::init(RandomAccessStream* stream, int bufferSize)
{
    this->m_buffStream.init(stream, nullptr, bufferSize);
    this->filePath = stream->filePath;
    this->m_stream = stream;
}
