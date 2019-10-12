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

extern SYSCORE_API HINSTANCE hInstance;
extern SYSCORE_API HINSTANCE sysHInst;
extern SYSCORE_API Stream *sysCon;
extern SYSCORE_API Stream *errCon;
extern SYSCORE_API HWND sysCurrWnd;
static HWND hWnd;
static WNDPROC lpPrevWndFunc;

// Not sure where to put these
extern SYSCORE_API int glnHeight;
extern SYSCORE_API int glnWidth;

#define nullptr 0
typedef unsigned __int8 uchar;   // actually used in game, check Graphics
typedef unsigned __int16 ushort; // actually used in game, check Graphics

#endif
