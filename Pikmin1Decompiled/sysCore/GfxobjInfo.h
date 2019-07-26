#pragma once
#ifndef GFXOBJINFO_H
#define GFXOBJINFO_H

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

class SYSCORE_API GfxobjInfo
{
public:
	GfxobjInfo() {}

	virtual void attach() {}
	virtual void detach() {}
};

#endif

