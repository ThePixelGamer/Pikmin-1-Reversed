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
	Stream* strm; // 0h
	char* buffer; // 4h
	char currentToken[0x100]; // 8h
	int pending; // 108h
	int unkVar2; // 10Ch
	int unkVar3; // 110h
	int currentChar; // 114h
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