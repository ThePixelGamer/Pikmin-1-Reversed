#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef BASEAPP_H
#define BASEAPP_H

#include "Nodes.h"

class SYSCORE_API BaseApp : public Node {
public:
// baseapp member variables (base class = node)
// 4h - vtbl ptr
// gap (28h)

	BaseApp();
};

#endif
