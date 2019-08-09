// AgeServer.h: interface for the AgeServer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AGESERVER_H__9949D1D6_D324_4F53_BC3F_203083ADCF35__INCLUDED_)
#define AFX_AGESERVER_H__9949D1D6_D324_4F53_BC3F_203083ADCF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#include "System/System.h"
#include "Colour.h"

class SYSCORE_API AgeServer : public AtxStream {
public:
	// 16h - AtxStream
	bool m_unk1;// 10h

	AgeServer(); // empty

	// END SECTION
	void Done(); // this->writeInt(200);
	void EndBitGroup(); // this->writeInt(0);
	void EndGroup(); // this->writeInt(303);
	void EndNode(); // this->writeInt(200);
	void EndOptionBox(); // this->writeInt(0);
	void EndSection(); // this->writeInt(301); this->m_unk = false

	// NEW SECTION
	//void NewBit(char *, unsigned __int32, unsigned __int32 ); // this->writeInt(1); blah blah
	// UH OH
	// void NewButton(char *, IDelegate *, int);
	// void NewButton(char *, IDelegate <AgeServer &> *, int);
	// void NewEditor(char *, AyuImage *, bool);
}

#endif // !defined(AFX_AGESERVER_H__9949D1D6_D324_4F53_BC3F_203083ADCF35__INCLUDED_)
