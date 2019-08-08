#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef RAMSTREAM_H
#define RAMSTREAM_H

#include "RandomAccessStream.h"

class SYSCORE_API RamStream : public RandomAccessStream { 
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
	virtual void	setPosition(int);
	virtual int		getLength();
	virtual void	setLength(int);
};

#endif