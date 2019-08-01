#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef STRING_H
#define STRING_H

class SYSCORE_API String {
public:
	int stringLen;
	char* string;

	String();
	String(int stringLength);
	String(char* string, int stringLength);

	double toFloat() { return 0.0; }
	int toInt();

	void init(int stringLength);
	void init(char* string, int stringLength);

	int calcHash();
	unsigned __int32 calcHash(char*);

	static int getLength(char*);
	int getLength();

	static char* dup(char*);
	char* dup();

	static void concat(char*, char*);
	static char* copy(char*, char*);
	static bool isSame(char*, char*);
	bool isSame(char*);
	bool isSame(String*);
	static bool isWhiteSpace(char);
	static bool copyUntil(char*, char*, char, char**);
	static bool equals(char*, char*);
	static bool contains(char*, char*);
	static bool contains(char*, char);
	bool contains(char*);
};

#endif