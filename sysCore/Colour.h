#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef COLOUR_H
#define COLOUR_H

#include "AgeServer.h"

class SYSCORE_API Colour  
{
public:
	unsigned __int8 R;
	unsigned __int8 G;
	unsigned __int8 B;
	unsigned __int8 A;

	Colour(unsigned __int8 r, unsigned __int8 g, unsigned __int8 b, unsigned __int8 a);
	Colour () {}

	void add(Colour &);
	void genAge(AgeServer &, char *);
	void lerp(Colour &, float);
	void lerpTo(Colour &, float, Colour &);
	void read(Stream &);
	void write(Stream &);
	void set(unsigned __int8 r, unsigned __int8 g, unsigned __int8 b, unsigned __int8 a);
};

#endif // #ifndef COLOUR_H
