#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef TEXIMG_H
#define TEXIMG_H

#include "../Stream/RandomAccessStream.h"
#include "../Nodes.h"

class SYSCORE_API TexImg : public CoreNode {
public:
	//0h vtable
	//10h CoreNode

	TexImg() : CoreNode("texImg") {}
};

#endif