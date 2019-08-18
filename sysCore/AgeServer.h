#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef AGESERVER_H
#define AGESERVER_H

#include "AgeAtx.h"
#include "IDelegate.h"
class Colour;

enum PROP_TYPE {
	UNK1 = 0,
	UNK2, // 1
	UNK3, // 2
	UNK4, // 3
	COLOUR, // 4
	UNK5, // 5
	UNK6, // 6
	UNK7, // 7
	UNK8 // 8
};

class SYSCORE_API AgeServer : public AtxStream {
public:
	// 16h - AtxStream
	bool m_unkOpen;// 10h

	AgeServer(); // empty

	virtual void close();

	void Done(); // this->writeInt(200);
	void EndBitGroup(); // this->writeInt(0);
	void EndGroup(); // this->writeInt(303);
	void EndNode(); // this->writeInt(200);
	void EndOptionBox(); // this->writeInt(0);
	void EndSection(); // this->writeInt(301); this->m_unk = false

	// NEW SECTION
	void NewBit(char*, unsigned __int32, unsigned __int32); // this->writeInt(1); blah blah
	// UH OH
	// void NewButton(char *, IDelegate *, int);
	// void NewButton(char *, IDelegate <AgeServer &> *, int);
	// void NewEditor(char *, AyuImage *, bool);
	void NewEditor(char*, Colour&);
	void NewEditor(char*, char*, int);
	void NewEditor(char*, char*, int, int, int);
	void NewEditor(char*, float*, float, float, int);

	void setOnChange(IDelegate1<AgeServer&>*);

	int writeProp(PROP_TYPE, void*);
	int writePropValue(PROP_TYPE, void*);

	bool Open();
};

#endif