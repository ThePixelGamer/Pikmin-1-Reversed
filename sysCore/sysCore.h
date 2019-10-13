#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#pragma once

#ifndef SYSCORE_H
#define SYSCORE_H

#include "Nodes/Node.h"
#include "Stream/Stream.h"
#include <Windows.h>
#pragma comment(lib, "ws2_32.lib") // Winsock Library

#define nullptr 0
#define TAU 6.2831855
#define PI 3.1415927

typedef unsigned __int8 uchar;   // actually used in game, check Graphics
typedef unsigned __int16 ushort; // actually used in game, check Graphics

extern SYSCORE_API HINSTANCE hInstance;
extern SYSCORE_API HINSTANCE sysHInst;
extern SYSCORE_API Stream *sysCon;
extern SYSCORE_API Stream *errCon;
extern SYSCORE_API HWND sysCurrWnd;
static HWND hWnd;
static WNDPROC lpPrevWndFunc;

SYSCORE_API float angDist(float, float);
SYSCORE_API float roundAng(float);
SYSCORE_API HANDLE startThread(void *, void *, int);

// Not sure where to put these
extern SYSCORE_API int glnHeight;
extern SYSCORE_API int glnWidth;

// overloading operators!
void *operator new(size_t);
void *operator new[](size_t);
void *operator new[](size_t, size_t);
void operator delete(void *);
void operator delete[](void *);

#endif
