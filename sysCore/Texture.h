#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef TEXTURE_H
#define TEXTURE_H

#include <Windows.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "GfxObject.h"

class SYSCORE_API Texture : public GfxObject {
public:
	//0h vtable
	GLuint* pixels; //14h
	GLuint tex; //18h

	Texture();

	virtual void attach();
	virtual void detach();
	virtual void makeResident();

	void grabBuffer(GLsizei, GLsizei, bool, bool);
};

#endif