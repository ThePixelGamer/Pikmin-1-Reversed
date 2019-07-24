#include "Stream.h"

Stream::Stream()
{
}


Stream::~Stream()
{
}

void Stream::print(char* Format, ...)
{
	va_list vaList;
	char* resultantString = nullptr;

	va_start(vaList, Format);
	vsprintf(resultantString, Format, vaList);

	int resultStringLength = strlen(resultantString);
	if (resultStringLength)
	{
		this->write(resultantString, resultStringLength);
	}
}

void Stream::vPrintf(char* Format, char* Args)
{
	char* resultantString = nullptr;

	vsprintf(resultantString, Format, Args);

	int resultStringLength = strlen(resultantString);
	if (resultStringLength)
	{
		this->write(resultantString, resultStringLength);
	}
}

int Stream::readInt()
{
	int c;
	this->read(&c, sizeof(int));
	return ((c & 0xFF000000) >> 24) | ((c & 0xFF0000) >> 8) | ((c & 0xFF00) << 8) | (c << 24);
}

char Stream::readByte()
{
	char c;
	this->read(&c, sizeof(unsigned char));
	return c;
}

short Stream::readShort()
{
	short c;
	this->read(&c, sizeof(short));
	return ((c & 0xFF00) >> 8) | (c << 8);
}

double Stream::readFloat()
{
	int c;
	this->read(&c, sizeof(float));
	c = ((c & 0xFF000000) >> 24) | ((c & 0xFF0000) >> 8) | ((c & 0xFF00) << 8) | (c << 24);
	return *reinterpret_cast<double*> (&c);
}

char * Stream::readString()
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

	if (str.stringLen < stringLength)
		str.init(stringLength);
	
	this->read(str.string, stringLength);

	str.string[stringLength] = 0; // null terminate string
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

void Stream::writeByte(unsigned __int8 toW)
{
	this->write(&toW, sizeof(toW));
}

void Stream::writeShort(__int16 toW)
{
	__int16 wr = ((toW & 0xFF00) >> 8) | (toW << 8);
	this->write(&wr, sizeof(wr));
}

void Stream::writeFloat(float toW)
{
	short* bigEndian = reinterpret_cast<short*>(&toW);
	std::reverse(bigEndian, bigEndian + sizeof(toW));
	this->write(&bigEndian, sizeof(toW));
}

void Stream::writeString(String& str)
{
	int stringLength = str.stringLen;
	this->writeInt(stringLength + 3);
	this->write(str.string, stringLength);
	stringLength += 3; // used instead of the v7 var
	for (int i = 0; ; ++i)
	{
		if (i >= stringLength - str.stringLen)
			break;
		this->writeByte(0);
	}
}

void Stream::writeString(char* toW)
{
	String tempVar(toW, 0);
	this->writeString(tempVar);
}
