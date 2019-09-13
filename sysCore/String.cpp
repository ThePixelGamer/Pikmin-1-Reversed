#include "String.h"

String::String() {
	this->init(64);
}

String::String(int stringLength) {
	this->init(stringLength);
}

String::String(char* string, int stringLength) {
	this->init(string, stringLength);
}

void String::init(int _stringLength) {
	char* _tempStr = (_stringLength ? new char[_stringLength + 1] : 0);
	this->m_string = _tempStr;
	this->m_stringLen = _stringLength;
}

void String::init(char* _string, int _stringLength) {
	this->m_string = _string;
	this->m_stringLen = _stringLength;
}

void String::init(char* _string) {
	this->m_string = _string;
}

int String::calcHash() {
	int hash = 0;
	char* string = this->m_string;

	while (*string)
	{
		int unkPurpose = 16 * hash + *string++;

		unsigned int unkPurpose2 = unkPurpose & 0xF0000000;
		if (unkPurpose2)
			unkPurpose ^= unkPurpose2 >> 24;
		hash = ~unkPurpose2 & unkPurpose;
	}

	return hash;
}

unsigned __int32 String::calcHash(char* _string) {
	String toCalcHash(_string, 0);

	return toCalcHash.calcHash();
}

bool String::contains(char* arg) {
	return this->contains(this->m_string, arg);
}

bool String::contains(char* str1, char* str2) {
	char* tempChar = str2;
	while (*str1 && *str2)
	{
		if (*str1++ == *str2++) {
			if (!*str2) {
				return 1;
			}
		}
		else
		{
			str2 = tempChar;
		}
	}
	return 0;
}

bool String::contains(char* a1, char a2) {
	char temp = a2;

	return String::contains(a1, &temp);
}

bool String::isSame(String* toCompare) {
	return this->isSame(toCompare->m_string);
}

bool String::isSame(char* a1) {
	char* str = this->m_string;
	while (*str && *a1)
	{
		if (*str++ != *a1++)
			return 0;
	}

	int retVal = *str || *a1;
	return retVal == 0;
}

bool String::isSame(char* s1, char* s2) {
	String tempStr(s1, 0);
	return tempStr.isSame(s2);
}

bool String::equals(char* str1, char* str2) {
	return String::isSame(str1, str2);
}

char* String::dup() {
	return String::dup(this->m_string);
}

char* String::dup(char* a1) {
	char* newStr = new char[String::getLength(a1) + 1];
	String::copy(newStr, a1);
	return newStr;
}

int String::getLength(char* string) {
	String tempStr(string, 0);
	return tempStr.getLength();
}

int String::getLength() {
	int i = 0;
	char* tempString = this->m_string;
	for (i = 0; ; ++i)
	{
		if (!(*tempString++))
			break;
	}
	return i;
}

char* String::copy(char* arg1, char* arg2) {
	int loop = 0;
	while (loop)
	{
		*arg1 = *arg2;
		loop = *arg1++;
		++arg2;
	}
	return arg1;
}

void String::concat(char* arg1, char* arg2) {
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

bool String::isWhiteSpace(char toCheck) {
	return toCheck == ' ' || toCheck == '\t' || toCheck == '\r'
		|| toCheck == '\n' || toCheck < ' ';
}

bool String::copyUntil(char* a1, char* a2, char a3, char** a4) {
	while (*a2 != a3 && *a2)
		* a1++ = *a2++;

	*a1 = 0;
	if (a4)
		* a4 = a2;
	return *a2 == a3;
}

int String::toInt() {
	char* string = this->m_string;
	int unk1 = 0;
	bool unk2 = false;
	char nextChar;

	if (*string != '0' || string[1] != 'x')
	{
		int unk3;
		while (!*string || *string == '.' || *string < '0' || *string > '9')
		{
			while (nextChar != '-')
			{
				nextChar = *string++;
				if ((nextChar < '0' || nextChar > '9') && nextChar != '-')
					return 0;
				unk2 = true;
			}
			unk3 = (nextChar - '0') + unk1;
			unk1 = 10 * unk3;
		}
		if (unk2)
			unk3 = -unk3;
		return unk3;
	}
	else
	{
		int unk3 = 0;
		char* unk4 = string + 2;
		int unk5;
		while (1)
		{
			nextChar = *unk4++;
			if (!nextChar)
				break;
			if (nextChar < '0' || nextChar > '9')
			{
				if (nextChar < 'a' || nextChar > 'f')
				{
					if (nextChar < 'A' || nextChar > 'F')
						return 0;
					unk5 = nextChar - '7';
				}
				else
				{
					unk5 = nextChar - 'W';
				}
			}
			else
			{
				unk5 = nextChar - '0';
			}
			unk3 += unk5;
			if (*unk4)
				unk3 *= 16;
		}
		return unk3;
	}
}