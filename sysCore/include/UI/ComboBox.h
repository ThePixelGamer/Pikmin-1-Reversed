#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <UI/UIWindow.h>

static char cBoxStringBuf[256];

class SYSCORE_API ComboBox : public UIWindow
{
public:
    // vtable 0h
    //(CoreNode: 4h-10h)
    //(Node: 14h-1Ch)
    //(UIFrame: 20h-40h)
    //(UIWindow: 50h-84h)
    UIWindow* m_boxWindow; // 88h
    int m_boxExStyle;      // 8Ch

    ComboBox(UIWindow*, int, int, int, bool);
    // destructor gets auto-gen'd

    void addOption(char*, bool);
    void selOption(int);

    virtual int processMessage(HWND, unsigned int, WPARAM, long);
    virtual void createWindow(LPCSTR, LPCSTR, HMENU);
    virtual void entryHandler(char*); // 58h
};

#endif