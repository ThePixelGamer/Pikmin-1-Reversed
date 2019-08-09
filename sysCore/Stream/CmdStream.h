#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef CMDSTREAM_H
#define CMDSTREAM_H

#include "Stream.h"

class SYSCORE_API CmdStream {
private:
	Stream* strm;
	char* buffer; //this + 4
	char currentToken[256];
	int pending;
	int currentChar;
	int unkVar2;
	int unkVar3;
public:
	static char* statbuff;

	CmdStream() {}
	CmdStream(Stream* strm);

	void init(Stream*);
	void fillBuffer(bool canFill);
	void copyToToken(int);

	char nextChar();
	bool isToken(char* Str);
	char* getToken(bool hasComments);
	char* skipLine();

	bool LineIsComment();
	bool whiteSpace(char toCheck);
	bool endOfCmds();
	bool endOfSection();
};

#endif