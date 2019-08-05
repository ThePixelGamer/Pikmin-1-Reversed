#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Vector3f.h"

class SYSCORE_API Graphics {
public:
	Vector3f test;

	Graphics();
	virtual void setVerticalFilter(char*);
};

#endif 
