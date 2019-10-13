#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef TOOLWINDOW_H
#define TOOLWINDOW_H

#include <UI/UIWindow.h>

class SYSCORE_API ToolWindow : public UIWindow
{
public:
    UIWindow* m_toolWindow; // 88h
    HINSTANCE m_unk11;      // 8Ch

    ToolWindow(UIWindow*, int, int, int, bool);

    void initTools(HINSTANCE, int, TBBUTTON*, tagTBADDBITMAP*);
    virtual int processMessage(HWND, unsigned int, WPARAM, long);
    virtual void createWindow(LPCSTR className, LPCSTR windowName, HMENU hMenu);
};
#endif