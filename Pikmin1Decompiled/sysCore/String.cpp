#include "String.h"



String::String()
{
}

String::String(int stringLength)
{
	this->init(stringLength);
}

String::String(char* string, int stringLength)
{
	this->init(string, stringLength);
}


String::~String()
{
}

void String::init(int stringLength)
{
	char *tempString;

	if (stringLength)
		tempString = new char[stringLength + 1]; // v2 = sub_10001AC3(a2 + 1);
	else
		tempString = 0; // equivalent to nullptr I think
	this->string = tempString;
	this->stringLen = stringLength;
}

void String::init(char* string, int stringLength)
{
	this->string = string;
	this->stringLen = stringLength;
}

int String::calcHash()
{
	char* tempString = this->string;
	int returnValue = 0;

	while (*tempString)
	{
		int unkPurpose = *tempString++ + (16 * returnValue);
		unsigned int unkPurpose2 = unkPurpose & 0xF0000000;
		if (unkPurpose2)
			unkPurpose ^= unkPurpose2 >> 24;
		returnValue = ~unkPurpose2 & unkPurpose;
	}

	return returnValue;
}

unsigned int String::calcHash(char* str)
{
	String tempString(str, 0);
	return this->calcHash();
}
