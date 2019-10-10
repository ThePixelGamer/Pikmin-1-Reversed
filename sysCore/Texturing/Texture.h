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

#include "../GfxObject.h"
#include "../Stream/RandomAccessStream.h"
#pragma comment(lib, "opengl32.lib")

class SYSCORE_API Texture : public GfxObject {
public:
	/*_WORD word0;
	  __declspec(align(4)) _WORD word4;
	  _WORD word6;
	  _WORD x;
	  _WORD y;
	  _DWORD dwordC;
	  _DWORD dword10;
	  _DWORD dword14;
	  _DWORD dword18;
	  _DWORD dword1C;
	  _DWORD dword20;
	  _DWORD dword24;
	  _DWORD dword28;
	  _DWORD dword2C;
	  _DWORD dword30;*/

	//0h vtable
	GLsizei width; //8h
	GLsizei height; //Ah

	GLuint* pixels; //14h
	GLuint tex; //18h


	Texture();

	virtual void attach();
	virtual void detach();
	virtual void makeResident();

	void read(RandomAccessStream&);
	void grabBuffer(GLsizei, GLsizei, bool, bool);
	unsigned __int8 getAlpha(int, int);
	unsigned __int8 getRed(int, int);
};

#endif