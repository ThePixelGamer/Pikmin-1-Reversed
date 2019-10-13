#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef EDITBOX_H
#define EDITBOX_H

#include <UI/ComboBox.h>

static char eBoxStringBuf[256];

class SYSCORE_API EditBox : public ComboBox
{
public:
    // vtable 0h
    //(CoreNode: 4h-10h)
    //(Node: 14h-1Ch)
    //(UIFrame: 20h-40h)
    //(UIWindow: 50h-84h)
    //(ComboBox: 88h-8Ch)

    EditBox(UIWindow*, int, int, int, bool);

    virtual void entryHandler(char* msg);
    virtual int processMessage(HWND, unsigned int, WPARAM, long);
};
#endif