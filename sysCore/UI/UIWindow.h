#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef UIWINDOW_H
#define UIWINDOW_H

#include "UIFrame.h"

void UIWINDOWPRINT(const char *fmt, ...);

class SYSCORE_API UIWindow : public UIFrame {
public:
  // vtable 0h
  //(CoreNode: 4h-10h)
  //(Node: 14h-1Ch)
  //(UIFrame: 20h-40h)
  RectArea m_unk1;    // 50h
  UIWindow *m_parent; // 60h
  HWND m_hWnd;        // 64h
  int m_dwStyle;      // 68h
  int m_dwExStyle;    // 6Ch
  int m_unk6;         // 70h
  int m_unk7;         // 74h
  int m_unk8;         // 78h
  int m_unk9;         // 7Ch
  bool m_unk10;       // 80h
  HMENU m_hMenu;      // 84h

  UIWindow();
  UIWindow(UIWindow *, int, int, int, bool);
  ~UIWindow();

  virtual void refreshWindow();                                    // 34h
  virtual void updateSizes(int, int);                              // 38h
  virtual void activate();                                         // 3Ch
  virtual int processMessage(HWND, unsigned int, WPARAM, long);    // 40h
  virtual LRESULT returnMessage(HWND, unsigned int, WPARAM, long); // 44h
  virtual HDWP resizeChildren(HDWP, RectArea &);                   // 48h
  virtual HDWP resizeFrame(HDWP, RectArea &);                      // 4Ch
  virtual void createWindow(LPCSTR, LPCSTR, HMENU);                // 50h
  virtual void dockTop(int, RectArea &, RectArea &);               // 54h

  void closeChildren();
  void initFrame(UIWindow *, int, int, int, bool);
  void sizeWindow(int, int, int);
  void updateMove(int, int);
};

#endif