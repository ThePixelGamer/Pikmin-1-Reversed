#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef ID
#define ID

#include "Stream/RandomAccessStream.h"
#include "sysCore.h"

class AgeServer;

class SYSCORE_API ID32 { // this will definitely have to be relooked at later
public:
	union {
		unsigned __int32 id;
		unsigned char cId[4];
	}; //unsure if they did this but it works and it's clean :)
	char sId[5]; // 0h

	ID32();
	ID32(unsigned __int32);

	void ageChangeID();
	void genAge(AgeServer&, char*);
	void match(unsigned __int32, char);
	void print();
	void read(RandomAccessStream&);
	void setID(unsigned __int32);
	void sprint(char*);
	void updateID();
	void updateString();
	void write(RandomAccessStream&);
};

#endif
