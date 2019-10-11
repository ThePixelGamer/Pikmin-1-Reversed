#include "UIWindow.h"
#include "UIMgr.h"

void UIWINDOWPRINT(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  char dest[1024];

  if (sysCon) {
    if ("uiWindow")
      sysCon->print("%s: ", "uiWindow");
    vsprintf(dest, fmt, args);
    if (strlen(dest)) {
      sysCon->write(dest, strlen(dest));
    }
  }
}

UIWindow::UIWindow() : UIFrame() {
  this->m_parent = 0;
  this->m_dwExStyle = 0;
  this->m_dwStyle = 0;
  this->m_unk10 = 0;
  this->m_hMenu = 0;
  this->m_unk7 = 0;
  this->m_unk1.set(0, 0, 0, 0);
}

UIWindow::UIWindow(UIWindow *parent, int unk2, int style, int exstyle,
                   bool unk5)
    : UIFrame() {
  this->m_unk7 = 0;
  this->m_unk10 = 0;
  this->m_hMenu = 0; // HMENU
  initFrame(parent, unk2, style, exstyle, unk5);
}

UIWindow::~UIWindow() { UIWINDOWPRINT("now closing window %s", this->name); }

void UIWindow::refreshWindow() {
  this->updateSizes(this->m_client.width(), this->m_client.height());
}

void UIWindow::updateSizes(int w, int h) {
  int frameX1 = this->m_frame.x1;
  int frameY1 = this->m_frame.y1;
  int v10 = w + (-this->m_zero.x1 + this->m_zero.x2);
  int v9 = h + (-this->m_zero.y1 + this->m_zero.y2);
  this->m_frame = RectArea(frameX1, frameY1, frameX1 + v10, frameY1 + v9);
  this->calcClientFromFrame(this->m_client);
  HDWP hWinPosInfo = BeginDeferWindowPos(40);
  if (this->Child()) {
    hWinPosInfo = this->resizeChildren(hWinPosInfo, RectArea(0, 0, w, h));
  }
  EndDeferWindowPos(hWinPosInfo);
}

void UIWindow::activate() {}

int UIWindow::processMessage(HWND hWnd, unsigned int Msg, WPARAM wParam,
                             long lParam) {
  switch (Msg) {
  case WM_MOVE: {
    UIWindow *windLong = (UIWindow *)GetWindowLongA(hWnd, 0);
    if (windLong)
      windLong->updateMove(lParam, lParam >> 16);
    return 0;
  }
  case WM_SIZE: {
    UIWindow *windLong = (UIWindow *)GetWindowLongA(hWnd, 0);
    if (windLong)
      windLong->updateSizes(lParam, lParam >> 16);
    return 0;
  }
  case WM_CLOSE: {
    UIWindow *windLong = (UIWindow *)GetWindowLongA(hWnd, 0);
    if (windLong) {
      this->closeChildren();
      nodeMgr->Del(windLong);
      SetWindowLong(hWnd, 0, 0);
    }
    return this->returnMessage(hWnd, Msg, wParam, lParam);
  }
  case WM_NCLBUTTONDOWN:
    if (wParam == 2 && GetFocus() != hWnd)
      SetFocus(hWnd);
    break;
  case WM_KEYDOWN:
    if (wParam == VK_ESCAPE)
      SendMessage(hWnd, WM_CLOSE, 0, 0);
    break;
  default:
    return this->returnMessage(hWnd, Msg, wParam, lParam);
  }
  return this->returnMessage(hWnd, Msg, wParam, lParam);
}

LRESULT UIWindow::returnMessage(HWND hWnd, unsigned int Msg, WPARAM wParam,
                                long lParam) {
  return DefWindowProc(hWnd, (UINT)Msg, wParam, lParam);
}

HDWP UIWindow::resizeChildren(HDWP hWinPosInfo, RectArea &rect) {
  for (CoreNode *i = Child(); i; i = i->Next()) {
    hWinPosInfo = this->resizeFrame(hWinPosInfo, rect);
  }
  return hWinPosInfo;
}

HDWP UIWindow::resizeFrame(HDWP hWinPosInfo, RectArea &rect) {
  return hWinPosInfo;
}

void UIWindow::createWindow(LPCSTR className, LPCSTR windowName, HMENU hMenu) {
  this->m_hMenu = hMenu;

  HWND hWndParent;
  if (this->m_parent)
    hWndParent = this->m_parent->m_hWnd;
  else
    hWndParent = 0;

  this->m_hWnd = CreateWindowExA(
      this->m_dwExStyle, className, windowName, this->m_dwStyle,
      this->m_frame.x1, this->m_frame.y1, this->m_frame.width(),
      this->m_frame.height(), hWndParent, this->m_hMenu, sysHInst, NULL);

  if (windowName)
    this->setName((char *)windowName);
  else
    this->setName((char *)className);

  if (!strcmp(className, "DUIGenWin") || !strcmp(className, "DUIClearWin"))
    SetWindowLong(this->m_hWnd, 0, (long)this);
}

void UIWindow::dockTop(int _height, RectArea &old, RectArea &newarea) {
  old.y1 = newarea.y1;
  int newY2 = (_height < newarea.height()) ? _height : newarea.height();
  old.y2 = newY2 + old.y1;
  newarea.y1 = old.y2;
}

void UIWindow::closeChildren() { // asm matches
  UIWindow *childNext;
  for (UIWindow *child = (UIWindow *)this->Child(); child; child = childNext) {
    childNext = (UIWindow *)child->Next();
    SendMessage(child->m_hWnd, WM_CLOSE, 0, 0);
  }
}

void UIWindow::initFrame(UIWindow *parent, int a2, int style, int exstyle,
                         bool a5) {
  this->m_parent = parent;
  this->m_dwStyle = style;
  this->m_dwExStyle = exstyle;
  this->m_unk6 = a2;
  this->m_unk10 = a5;

  int x1 = 32;
  int y1 = 32;
  int x2 = 128;
  int y2 = 128;

  tagRECT rect;
  rect.left = 32;
  rect.top = 32;
  rect.right = 128;
  rect.bottom = 128;

  AdjustWindowRectEx(&rect, this->m_dwStyle, false, this->m_dwExStyle);

  // literally no point in this because 32 - 32 = 0 and 128 - 128
  this->m_zero.x1 = rect.left - x1;
  this->m_zero.y1 = rect.top - y1;
  this->m_zero.x2 = rect.right - x2;
  this->m_zero.y2 = rect.bottom - y2;

  if (this->m_unk10)
    this->m_zero.y1 -= GetSystemMetrics(
        SM_CYMENU); //     The height of a single-line menu bar, in pixels.
  if (this->m_dwStyle & WS_VSCROLL)
    this->m_zero.x2 += GetSystemMetrics(
        SM_CXVSCROLL); // The width of a vertical scroll bar, in pixels.
  if (this->m_dwStyle & WS_HSCROLL)
    this->m_zero.y2 += GetSystemMetrics(
        SM_CYHSCROLL); // The height of a horizontal scroll bar, in pixels.

  if (style & WS_CHILDWINDOW)
    this->m_parent->add(this);
  else
    uiMgr->add(this);
}

void UIWindow::sizeWindow(int x, int y, int a2) {
  int w;
  int h;
  x += -this->m_zero.x1 + this->m_zero.x2;
  y += -this->m_zero.y1 + this->m_zero.y2;
  this->m_unk8 = x;
  this->m_unk9 = y;
  if (a2 == 1) {
    RectArea rect;
    if (m_dwStyle & WS_CHILDWINDOW) {
      rect = this->m_parent->m_client;
    } else {
      SystemParametersInfoA(SPI_GETWORKAREA, 0, &rect, 0);
    }

    w = rect.width() / 2 + rect.x1 - this->m_unk8 / 2;
    h = rect.height() / 2 + rect.y1 - this->m_unk9 / 2;

    if (w < 0)
      w = 0;
    if (h < 0)
      h = 0;
    if (this->m_unk8 > rect.width())
      this->m_unk8 = rect.width();
    if (this->m_unk9 > rect.height())
      this->m_unk9 = rect.height();
  } else {
    h = 0;
    w = 0;
  }

  this->setFrame(RectArea(w, h, w + x, h + y));
}

void UIWindow::updateMove(int x, int y) { // unsure if asm matches
  int newX = x + this->m_zero.x1;
  int newY = y + this->m_zero.y1;
  int addedX = this->m_frame.width();
  int addedY = this->m_frame.height();
  this->m_frame = RectArea(newX, newY, newX + addedX, newY + addedY);
  this->calcClientFromFrame(this->m_client);
}