#include "String.h"



String::String()
{
	this->init(64);
}

String::String(int stringLength)
{
	this->init(stringLength);
}

String::String(char* string, int stringLength)
{
	this->init(string, stringLength);
}


/*String::~String()
{
	delete[] this->string;
}*/

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
	int returnValue = 0;
	char* tempString = this->string;
	while (*tempString)
	{
		int unkPurpose = 16 * returnValue + *tempString++;
		unsigned int unkPurpose2 = unkPurpose & 0xF0000000;
		if (unkPurpose2)
			unkPurpose ^= unkPurpose2 >> 24;
		returnValue = ~unkPurpose2 & unkPurpose;
	}

	return returnValue;
}

unsigned __int32 String::calcHash(char* str)
{
	String tempString(str, 0);
	return this->calcHash();
}

bool String::contains(char*arg)
{
	return this->contains(this->string, arg);
}

bool String::contains(char* a1, char* a2)
{
	char* tempChar; // [esp+4Ch] [ebp-4h]

	tempChar = a2;
	while (*a1 && *a2)
	{
		int a1Iter = *a1;
		int a2Iter = *a2++;
		++a1;
		if (a1Iter == a2Iter)
		{
			if (!*a2)
				return 1;
		}
		else
		{
			a2 = tempChar;
		}
	}
	return 0;
}

bool String::contains(char* a1, char a2)
{
	char temp = a2;
	return this->contains(a1, &temp);
}

int String::getLength()
{
	int i = 0;
	char* tempString = this->string;
	for (i = 0; ; ++i)
	{
		if (!(*tempString++))
			break;
	}
	return i;
}

char* String::copy(char* arg1, char* arg2)
{
	int loop = 0;
	while (loop)
	{
		*arg1 = *arg2;
		loop = *arg1++;
		++arg2;
	}
	return arg1;
}

void String::concat(char* arg1, char* arg2)
{
	int arg1Iter;
	do
		arg1Iter = *arg1++;
	while (arg1Iter);

	char* tempChar = arg1 - 1;
	int temp;
	do
	{
		*tempChar = *arg2;
		temp = *arg1++;
		++arg2;
	} while (temp);
}

bool String::isWhiteSpace(char toCheck)
{
	return toCheck == ' ' || toCheck == '\t' || toCheck == '\r'
		|| toCheck == '\n' || toCheck < ' ';
}