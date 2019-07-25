#include "Stream.h"

Stream::Stream()
{
}

void Stream::print(char* Format, ...)
{
	va_list vaList;
	char resultantString;

	va_start(vaList, Format);
	vsprintf(&resultantString, Format, vaList);

	if (strlen(&resultantString))
	{
		this->write(&resultantString, strlen(&resultantString));
	}
}

void Stream::vPrintf(char* Format, char* Args)
{
	char resultantString;

	vsprintf(&resultantString, Format, Args);

	
	if (strlen(&resultantString))
	{
		int resultStringLength = strlen(&resultantString);
		this->write(&resultantString, resultStringLength);
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
	this->readString(String(string, stringLength));
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

void Stream::writeShort(short toW)
{
	short wr = ((toW & 0xFF00) >> 8) | (toW << 8);
	this->write(&wr, sizeof(wr));
}

void Stream::writeFloat(float toW)
{
	float bigEndian = (((unsigned int)toW & 0xFF000000) >> 24) | (((unsigned int)toW & 0xFF0000) >> 8) | (((unsigned int)toW & 0xFF00) << 8) | ((unsigned __int16)toW << 24);
	this->write(&bigEndian, sizeof(toW));
}

void Stream::writeString(String& str)
{
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int i; // [esp+4Ch] [ebp-10h]
  int v7; // [esp+54h] [ebp-8h]

  v2 = (str.getLength() + 3);
  v2 = v2 & 0xFC;
  v7 = v2;

  this->writeInt(v2);
  v3 = str.getLength();
  this->write(str.string, v3);
  
  char v6 = 0; // [esp+50h] [ebp-Ch]
  for ( i = 0; ; ++i )
  {
    v4 = str.getLength();
    if ( i >= v7 - v4 )
      break;
    this->write(&v6, 1);
  }
}

void Stream::writeString(char* toW)
{
	String tempStr(toW, 0);
	this->writeString(tempStr);
}
