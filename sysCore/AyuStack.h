// AyuStack.h: interface for the AyuStack class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AYUSTACK_H__90695B59_0425_4268_BF1F_EF8B26449CFA__INCLUDED_)
#define AFX_AYUSTACK_H__90695B59_0425_4268_BF1F_EF8B26449CFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AyuStack  
{
public:
	int allocType; //0h
	int size; //4h
	int used; //8h
	void * m_unk1; //Ch
	AyuStack();
	virtual ~AyuStack();

};

#endif // !defined(AFX_AYUSTACK_H__90695B59_0425_4268_BF1F_EF8B26449CFA__INCLUDED_)
