#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef AYUHEAP_H
#define AYUHEAP_H

#include "AyuStack.h"

class AyuHeap : public AyuStack {
public:
	void init(char*, int, void*, int);
};

#endif