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
	const char* m_buffer; //8h
	int m_position; //Ch
	size_t m_length; //10h

	RamStream(const char*, size_t);

	virtual void	read(void*, int);
	virtual void	write(void*, int);
	virtual int		getPending();
	virtual int		getPosition();
	virtual void	setPosition(int);
	virtual int		getLength();
	virtual void	setLength(int);
};

#endif