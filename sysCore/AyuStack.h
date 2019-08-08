// AyuStack.h: interface for the AyuStack class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AYUSTACK_H__90695B59_0425_4268_BF1F_EF8B26449CFA__INCLUDED_)
#define AFX_AYUSTACK_H__90695B59_0425_4268_BF1F_EF8B26449CFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#include "System/System.h"

class SYSCORE_API AyuStack  
{
public:
	int m_allocType; //0h
	int m_size; //4h
	int m_used; //8h
	char* m_unk1; //Ch
	int m_topSize; //10h
	char* m_unk2; //14h ( this + 20 )
	int m_topFree; //18h

	bool active; //1Dh ( this + 29 )
	char* name; //20h ( this + 32 )

	AyuStack();

	bool checkOverflow();
	void checkStack();
	void create();

	int getFree();
	int getMaxFree();
	int getSize();
	int getTopUsed();
	int getUsed();

	void inactivate();

	void pop();
	void push(int);

	void reset(int);
};

#endif // !defined(AFX_AYUSTACK_H__90695B59_0425_4268_BF1F_EF8B26449CFA__INCLUDED_)
