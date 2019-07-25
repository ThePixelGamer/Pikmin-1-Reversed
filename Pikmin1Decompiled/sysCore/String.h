#pragma once

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

class SYSCORE_API String
{
public:
	int stringLen;
	char * string;

	String();
	String(int stringLength);
	String(char* string, int stringLength);
	//~String();

	void init(int stringLength);
	void init(char* string, int stringLength);

	int calcHash();
	unsigned __int32 calcHash(char* str);

	bool contains(char*);
	static bool contains(char*, char*);
	bool contains(char*, char);

	int getLength();

	static char* copy(char* arg1, char* arg2);
	static void concat(char* arg1, char* arg2);
	static bool isWhiteSpace(char toCheck);
};

