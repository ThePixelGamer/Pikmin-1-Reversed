#pragma once
class String
{
private:
	char * string = nullptr;
	int stringLen = 0;
public:
	String();
	String(int stringLength);
	String(char* string, int stringLength);
	~String();

	void init(int stringLength);
	void init(char* string, int stringLength);

	int calcHash();
	unsigned int calcHash(char* str);
};

