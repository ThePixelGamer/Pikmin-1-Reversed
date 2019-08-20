#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef OBJINFO_H
#define OBJINFO_H

#include "ID32.h"

class SYSCORE_API GfxobjInfo {
public:
	//vtable - 0h
	GfxobjInfo* prev; //4h
	GfxobjInfo* next; //8h
	char* str; //Ch
	ID32 id32; //10h
	void* unused; //1Ch

	GfxobjInfo();

	virtual void attach();
	virtual void detach();

	void insertAfter(GfxobjInfo* a2);
	void remove();
};

class AnimData;

class SYSCORE_API AnmobjInfo : public GfxobjInfo {
public:
	//(GfxobjInfo: 0h-1Ch)
	AnimData* animData; 

	AnmobjInfo();

	virtual void detach();
};

#endif 