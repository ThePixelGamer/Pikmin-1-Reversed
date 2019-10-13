#include <Stream/Stream.h>

Stream::Stream() {}

void Stream::print(char* Format, ...)
{
    char Dest[256]; // [esp+50h] [ebp-400h]
    va_list va;     // [esp+460h] [ebp+10h]

    va_start(va, Format);
    vsprintf(Dest, Format, va);
    if (strlen(Dest))
    {
        this->write(Dest, strlen(Dest));
    }
}

void Stream::vPrintf(char* Format, char* Args)
{
    char resultantString[256];

    vsprintf(resultantString, Format, Args);

    if (strlen(resultantString))
    {
        this->write(resultantString, strlen(resultantString));
    }
}

int Stream::readInt()
{
    int c;
    this->read(&c, sizeof(int));
    return ((c & 0xFF000000) >> 24) | ((c & 0xFF0000) >> 8) | ((c & 0xFF00) << 8) | (c << 24);
}

unsigned __int8 Stream::readByte()
{
    unsigned __int8 c;
    this->read(&c, sizeof(unsigned __int8));
    return c;
}

short Stream::readShort()
{
    short c;
    this->read(&c, sizeof(short));
    return ((c & 0xFF00) >> 8) | (c << 8);
}

float Stream::readFloat()
{
    int c;
    this->read(&c, sizeof(float));
    c = (c << 24) | ((c & 0xFF00) << 8) | ((c & 0xFF0000) >> 8) | ((c & 0xFF000000) >> 24);
    return *reinterpret_cast<float*>(&c);
}

char* Stream::readString()
{
    int stringLength = this->readInt();
    char* returnValue = new char[stringLength + 1];

    this->read(returnValue, stringLength);

    returnValue[stringLength] = 0;
    return returnValue;
}

void Stream::readString(String& str)
{
    int stringLength = this->readInt();

    if (str.m_stringLen < stringLength)
        str.init(stringLength);

    this->read(str.m_string, stringLength);

    str.m_string[stringLength] = 0; // null terminate string
}

void Stream::readString(char* string, int stringLength)
{
    String tempVar(string, stringLength);
    this->readString(tempVar);
}

void Stream::writeInt(int toW)
{
    unsigned int wr = ((toW & 0xFF000000) >> 24) | ((toW & 0xFF0000) >> 8) | ((toW & 0xFF00) << 8) | (toW << 24);
    this->write(&wr, sizeof(wr));
}

void Stream::writeByte(unsigned __int8 toW) { this->write(&toW, sizeof(toW)); }

void Stream::writeShort(short toW)
{
    short wr = ((toW & 0xFF00) >> 8) | (toW << 8);
    this->write(&wr, sizeof(wr));
}

void Stream::writeFloat(float toW)
{
    unsigned int temp = *reinterpret_cast<unsigned int*>(&toW);
    temp = (temp << 24) | ((temp & 0xFF00) << 8) | ((temp & 0xFF0000) >> 8) | ((temp & 0xFF000000) >> 24);
    this->write(&temp, sizeof(float));
}

void Stream::writeString(String& str)
{
    int strleng = (str.getLength() + 3) & ~3;
    this->writeInt(strleng);
    this->write(str.m_string, str.getLength());

    char tempBuf = 0;
    for (int i = 0;; ++i)
    {
        if (i >= strleng - str.getLength())
            break;
        this->write(&tempBuf, 1);
    }
}

void Stream::writeString(char* toW)
{
    String tempStr(toW, 0);
    this->writeString(tempStr);
}
