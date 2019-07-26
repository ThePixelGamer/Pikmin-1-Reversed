#include "CmdStream.h"

void * CmdStream::statbuff;

CmdStream::CmdStream(Stream * strm)
{
	this->init(strm);
}

void CmdStream::init(Stream* stream)
{
	this->buffer = 0;
	if (!CmdStream::statbuff)
	{
		CmdStream::statbuff = malloc(0x8000);
	}
	memset (CmdStream::statbuff, 0, 0x8000);
	this->strm = stream;
	this->pending = this->strm->getPending();
	this->currentChar = 0;
	this->unkVar2 = 0;
	this->unkVar3 = 0;
	this->buffer = CmdStream::statbuff;
	this->fillBuffer(1);
}

void CmdStream::fillBuffer(bool canFill)
{
	if (canFill || this->currentChar - this->unkVar3 >= 0x4000)
	{
		if (this->unkVar2)
		{
			memcpy((char *)this->buffer + this->unkVar3, (char *)this->buffer + this->unkVar3 + 0x4000, 0x4000);
			this->buffer = (char *)this->buffer - 0x4000;
			this->unkVar3 += 0x4000;
		}

		int result = this->unkVar2 != 0 ? 0x4000 : 0x8000;

		if (this->pending - this->unkVar2 < result)
			result = this->pending - this->unkVar2;

		this->strm->read((char *)this->buffer + this->unkVar2, result);
		this->unkVar2 += result;
	}
}

bool CmdStream::LineIsComment()
{
 return  *((char *)this->buffer + this->currentChar) == '#'
      || *((char *)this->buffer + this->currentChar) == '/' 
	  && *((char *)this->buffer + this->currentChar + 1) == '/';
}

void CmdStream::copyToToken(int length)
{
	for (int i = 0; i < length; ++i)
	{
		char currentChar = *((char *)this->buffer + i + this->currentChar);

		if (currentChar == '\t')
			currentChar = ' ';
		this->currentToken[i] = currentChar;
	}
	this->currentToken[i] = 0;
}

bool CmdStream::endOfCmds()
{
	this->fillBuffer(0);
	while (this->currentChar < this->pending && 
		this->whiteSpace( *((char*)this->buffer + this->currentChar)) )
	{
		this->currentChar++;
	}
	
	if (this->currentChar < this->pending)
		return *((char *)this->buffer + this->currentChar) == -1;

	else
		return 1;
		
}

bool CmdStream::whiteSpace(char toCheck)
{
	return !toCheck 
		 || toCheck == '\n' 
		 || toCheck == '\r' 
		 || toCheck == '\t'
		 || toCheck == ' '
		 || toCheck == ',';
}

bool CmdStream::endOfSection()
{
	this->fillBuffer(0);
	return *( (char *)this->buffer + this->currentChar ) == '}';
}

char* CmdStream::getToken(bool hasComments)
{
	this->fillBuffer(0);

	if (hasComments)
	{
		while (this->LineIsComment())
			this->skipLine();
	}

	int currChar = this->currentChar;
	char tempIdentifier = 0;
	
	if ( *((char *)this->buffer + currChar) == '"' || ( *((char *)this->buffer + currChar)) == '\'')
	{
		tempIdentifier = 1;
		++currChar;
		++this->currentChar;
	}
 
	while(1)
	{
		int shouldBreak;
		if (tempIdentifier)
		{
			shouldBreak = *((char *)this->buffer + currChar) == '"' || *((char *)this->buffer + currChar) == '\'' ? 0 : 1;;
		}

		else
		{
			shouldBreak = this->whiteSpace(*((char *)this->buffer + currChar)) == 0;
		}

		if (!shouldBreak)
			break;

		++currChar;

	}

	this->copyToToken(currChar - this->currentChar);

	if (tempIdentifier)
		this->currentToken[currChar++ - this->currentChar] = 0;

	while (currChar < this->pending && this->whiteSpace( *((char*) this->buffer + currChar) ))
		++currChar;

	this->currentChar = currChar;
	return this->currentToken;
}

char* CmdStream::skipLine()
{
	this->fillBuffer(0);
    for 	(int i = this->currentChar;
			 i < this->pending && *((char *)this->buffer + i) != '\n' && *((char *)this->buffer + i) != '\r';
			 ++i)
			 { ; }

	this->copyToToken(i - this->currentChar);

	while (*((char *)this->buffer + i) == '\n' || *((char *)this->buffer + i) == '\r')
		++i;

	this->currentChar = i;

	return this->currentToken;
}

char CmdStream::nextChar()
{
	return *((char *)this->buffer + this->currentChar);
}

char CmdStream::isToken(char * Str)
{
	if (!strlen(this->currentToken))
		return 0;

	if (strlen(this->currentToken) != strlen(Str))
		return 0;

	for (int i = 0; i < strlen(this->currentToken); ++i)
	{
		if (Str[i] != this->currentToken[i])
			return 0;
	}

	return 1;
}