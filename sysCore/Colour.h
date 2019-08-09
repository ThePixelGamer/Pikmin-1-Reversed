#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef COLOUR_H
#define COLOUR_H

#include "AgeServer.h"

class Colour  
{
public:
	char R;
	char G;
	char B;
	char A;

	Colour(char r, char g, char b, char a);
	Colour () {}

	void add(Colour &);
	void genAge(AgeServer &, char *);
	void lerp(Colour &, float);
	void lerpTo(Colour &, float, Colour &);
	void read(Stream &);
	void set(unsigned __int8 r, unsigned __int8 g, unsigned __int8 b, unsigned __int8 a);
	void write(Stream &);
};

#endif // #ifndef COLOUR_H
