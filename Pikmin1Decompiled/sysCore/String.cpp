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

	return String::contains(a1, &temp);
}

bool String::isSame(String * a1)
{
	return this->isSame(a1->string);
}

bool String::isSame(char * a1)
{
	char * str = this->string;
	while (*str && *a1)
	{
		if (*str++ != *a1++)
			return 0;
	}

	int retVal = *str || *a1;
	return retVal == 0;
}

bool String::isSame(char * s1, char * s2)
{
	String tempStr(s1, 0);
	return tempStr.isSame(s2);
}

bool String::equals(char * str1, char* str2)
{
	return String::isSame(str1, str2);
}

char * String::dup()
{
	return String::dup(this->string);
}

char * String::dup(char * a1)
{
	char * newStr = new char[String::getLength(a1) + 1];
	String::copy(newStr, a1);
	return newStr;
}

int String::getLength(char * string)
{
	String tempStr(string, 0);
	return tempStr.getLength();
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
bool String::copyUntil(char *a1, char *a2, char a3, char **a4)
{
	while ( *a2 != a3 && *a2 )
		*a1++ = *a2++;

	*a1 = 0;
	if ( a4 )
		*a4 = a2;
	return *a2 == a3;
}

int String::toInt() {
    int ret = 0;
    char nextChar; // [esp+60h] [ebp-8h]
    char* string = this->string;

    if(*string != '0' || string[1] != 'x') {
        bool unk2 = false;
        ret = (nextChar - '0');
        while(true) {
          while(true) {
            nextChar = *(string++);
            if((nextChar < '0' || nextChar > '9') && nextChar != '-')
              return 0;
            if(nextChar != '-')
              break;
            unk2 = true;
          }
          if(!*string || *string == '.' || *string < '0' || *string > '9')
            break;
        }
        if(unk2)
          ret = -ret;
    }
    else {
        char* stringa = string + 2;
        while(true) {
            int v2;
            nextChar = *(stringa++);
            if(!nextChar)
                break;
            if(nextChar < '0' || nextChar > '9') {
              if(nextChar < 'a' || nextChar > 'f') {
                if(nextChar < 'A' || nextChar > 'F')
                  return 0;
                v2 = nextChar - '7';
              }
              else {
                v2 = nextChar - 'W';
              }
            }
            else {
              v2 = nextChar - '0';
            }
            ret += v2;
            if(*stringa)
              ret *= 16;
        }
    }
    return ret;
}