// RamStream.h: interface for the RamStream class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RAMSTREAM_H__CCD290D9_3EEE_4EE0_BE2E_0ED103F3223F__INCLUDED_)
#define AFX_RAMSTREAM_H__CCD290D9_3EEE_4EE0_BE2E_0ED103F3223F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#include "STREAM\RandomAccessStream.h"

class SYSCORE_API RamStream : public RandomAccessStream  
{
public:
	//0h - vtblPtr
	int m_unk1; //4h
	char * m_buffer; //Ch
	int m_position; //10h
	int m_length; //14h
	
	RamStream(void *, int);

	virtual void	read(void *, int);
	virtual void	write(void *, int);

	virtual int		getPending();

	virtual int		getPosition();
	virtual void	setLength(int);

	virtual int		getLength();
	virtual void	setPosition(int);
};

#endif // !defined(AFX_RAMSTREAM_H__CCD290D9_3EEE_4EE0_BE2E_0ED103F3223F__INCLUDED_)
