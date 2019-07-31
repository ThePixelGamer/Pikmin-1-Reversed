#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef GFXOBJINFO_H
#define GFXOBJINFO_H

class SYSCORE_API GfxobjInfo
{
public:
	GfxobjInfo() {}

	virtual void attach() {}
	virtual void detach() {}
};

#endif