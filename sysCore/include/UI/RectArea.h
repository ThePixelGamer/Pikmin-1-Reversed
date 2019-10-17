#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef RECTAREA_H
#define RECTAREA_H

#include <sysCore.h>
#include <CommCtrl.h>
#pragma comment(lib, "comctl32.lib")

class SYSCORE_API RectArea
{
public:
    int x1; // 0h
    int y1; // 4h
    int x2; // 8h
    int y2; // Ch

    RectArea();
    RectArea(int x1, int y1, int x2, int y2);

    int height();
    int width();
    bool pointInside(int, int);
    void set(int, int, int, int);
};

#endif