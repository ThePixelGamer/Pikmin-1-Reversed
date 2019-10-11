#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef AGESERVER_H
#define AGESERVER_H

#include "Atx/AtxStream.h"
#include "IDelegate.h"
class Colour;

enum PROP_TYPE {
	INT_PROP = 0,
	FLOAT_PROP, // 1
	UNK3, // 2
	UNK4, // 3
	COLOUR, // 4
	UNK5, // 5
	STRING_PROP, // 6
	OPTIONBOX, // 7
	UNK8, // 8
	UNK9 // 9
};

class SYSCORE_API AgeServer : public AtxStream {
public:
	// 16h - AtxStream
	bool m_sectionStarted;// 10h

	AgeServer();

	virtual void close() {}

	void Done();
	void EndBitGroup();
	void EndGroup();
	void EndNode();
	void EndOptionBox();
	void EndSection();

	// NEW SECTION
	void NewBit(char*, unsigned __int32, unsigned __int32);

	void NewButton(char *, IDelegate *, int);
	void NewButton(char *, IDelegate1<AgeServer &> *, int);
	void NewEditor(char*, class AyuImage*, bool) {}
	void NewEditor(char*, Colour&);
	void NewEditor(char*, char*, int);
	void NewEditor(char*, char*, int, int, int);
	void NewEditor(char*, float*, float, float, int);
	void NewNodeWindow(char*);

	void setOnChange(IDelegate*);
	void setOnChange(IDelegate1<AgeServer&>*);
	void setSectionRefresh(IDelegate1<AgeServer&>*);

	void StartSection(char*, bool);
	void StartGroup(char*);

	int writeProp(PROP_TYPE, void*);
	int writePropValue(PROP_TYPE, void*);

	bool Open();
	bool getOpenFilename(String&, char*);
};

#endif