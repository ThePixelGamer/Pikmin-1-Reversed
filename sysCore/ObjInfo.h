#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef ObjInfo
#define ObjInfo

#include "ID32.h"

class SYSCORE_API GfxobjInfo {
public:
	//vtable - 0h
	int unk1; //4h
	int unk2; //8h
	char* str; //Ch
	ID32 unk3; //10h
	int unk4; //1Ch

	GfxobjInfo();

	void insertAfter(GfxobjInfo* a2);
};

#endif 