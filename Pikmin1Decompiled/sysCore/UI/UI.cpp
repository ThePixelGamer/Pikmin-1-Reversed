#include "UI.h"

//////////////////////////////////////////////////////////////////////
// RectArea class functions
//////////////////////////////////////////////////////////////////////

RectArea::RectArea() {
	this->x1 = 0;
	this->y1 = 0;
	this->x2 = 0;
	this->y2 = 0;
}

RectArea::RectArea(int x_1, int y_1, int x_2, int y_2) {
	this->x1 = x_1;
	this->y1 = y_1;
	this->x2 = x_2;
	this->y2 = y_2;
}

int RectArea::height() { return this->y2 - this->y1; }
int RectArea::width() { return this->x2 - this->x1; }
bool RectArea::pointInside(int x, int y) {
	return x > this->x1&& x < this->x2
		&& y > this->y1&& y < this->y2;
}

void RectArea::set(int x_1, int y_1, int x_2, int y_2) {
	this->x1 = x_1;
	this->y1 = y_1;
	this->x2 = x_2;
	this->y2 = y_2;
}

//////////////////////////////////////////////////////////////////////
// UIFrame class functions
//////////////////////////////////////////////////////////////////////

UIFrame::UIFrame() : Node("UIFrame") { }

void UIFrame::calcClientFromFrame(RectArea& client) {
	client.x1 = 0;
	client.y1 = 0;
	client.x2 = this->m_frame.width() - (-this->m_zero.x1 + this->m_zero.x2);
	client.y2 = this->m_frame.height() - (-this->m_zero.y1 + this->m_zero.y2);
}

void UIFrame::calcFrameFromClient(RectArea & frame) {
	frame.x1 += this->m_zero.x1;
	frame.y1 += this->m_zero.y1;
	frame.x2 = (frame.x1 + this->m_client.x2) + (-this->m_zero.x1 + this->m_zero.x2);
	frame.y2 = (frame.y1 + this->m_client.y2) + (-this->m_zero.y1 + this->m_zero.y2);
}

void UIFrame::setClient(RectArea & client) {
	this->m_client = client;
	calcFrameFromClient(this->m_frame);
}

void UIFrame::setFrame(RectArea & frame) {
	this->m_frame = frame;
	calcClientFromFrame(this->m_client);
}

//////////////////////////////////////////////////////////////////////
// UIWindow class functions
//////////////////////////////////////////////////////////////////////

UIWindow::UIWindow() : UIFrame() {
	this->m_parent = 0;
	this->m_dwExStyle = 0;
	this->m_dwStyle = 0;
	this->m_unk10 = 0;
	this->m_hMenu = 0;
	this->m_unk7 = 0;
	this->m_unk1.set(0, 0, 0, 0);
}

UIWindow::UIWindow(UIWindow * unk1, int unk2, int unk3, int unk4, bool unk5) : UIFrame() {
	this->m_unk7 = 0;
	this->m_unk10 = 0;
	this->m_hMenu = 0; //HMENU
	initFrame(unk1, unk2, unk3, unk4, unk5);
}

void UIWindow::refreshWindow() {
	updateSizes(this->m_client.width(), this->m_client.height());
}

void UIWindow::updateSizes(int w, int h) {
	int v12 = this->m_frame.x1;
	int v11 = this->m_frame.y1;
	int v10 = w + (-this->m_zero.x1 + this->m_zero.x2);
	int v9 = h + (-this->m_zero.y1 + this->m_zero.y2);
	this->m_frame = RectArea(v12, v11, v12 + v10, v11 + v9);
	calcClientFromFrame(this->m_client);
	HDWP hWinPosInfo = BeginDeferWindowPos(40);
	if (Child()) {
		hWinPosInfo = resizeChildren(hWinPosInfo, RectArea(0, 0, w, h));
	}
	EndDeferWindowPos(hWinPosInfo);
}

void UIWindow::activate() {

}

int UIWindow::processMessage(HWND hWnd, unsigned int Msg, unsigned int wParam, long lParam) {
	/*unsigned int v6; // [esp+4Ch] [ebp-18h]
	unsigned int unusedInt; // [esp+50h] [ebp-14h]
	struct Node* v10; // [esp+5Ch] [ebp-8h]

	unusedInt = Msg - 3;
	switch (Msg)
	{
	case WM_MOVE:
		UIWindow* uiWind = (UIWindow*)GetWindowLongA(hWnd, 0);
		if (v8)
			uiWind->updateMove(lParam, lParam >> 16);
		return 0;

	case WM_SIZE:
		long windowLong = GetWindowLongA(hWnd, 0);
		if (windowLong)
			(*(*v9 + 56))(v9, lParam, lParam >> 16);
		return 0;

	case WM_CLOSE:
		v10 = GetWindowLongA(hWnd, 0);
		if (v10)
		{
			UIWindow::closeChildren(this);
			NodeMgr::Del(nodeMgr, v10);
			SetWindowLongA(hWnd, 0, 0);
		}
		return (*(*this + 68))(this, hWnd, Msg, wParam, lParam);

	case WM_NCLBUTTONDOWN:
		if (wParam == 2 && GetFocus() != hWnd)
			SetFocus(hWnd);
		break;

	case WM_KEYDOWN:
		v6 = wParam;
		if (wParam == 27)
			SendMessageA(hWnd, WM_CLOSE, 0, 0);
		break;

	default:*/
		return this->returnMessage(hWnd, Msg, wParam, lParam);
	//}
}

LRESULT UIWindow::returnMessage(HWND hWnd, unsigned int Msg, unsigned int wParam, long lParam) {
	return DefWindowProc(hWnd, (UINT)Msg, (WPARAM)wParam, lParam);
}

HDWP UIWindow::resizeChildren(HDWP hWinPosInfo, RectArea & rect) {
	for (CoreNode* i = Child(); i; i = i->Next()) {
		hWinPosInfo = resizeFrame(hWinPosInfo, rect);
	}
	return hWinPosInfo;
}

HDWP UIWindow::resizeFrame(HDWP hWinPosInfo, RectArea & rect) {
	return hWinPosInfo;
}

void UIWindow::createWindow(LPCSTR className, LPCSTR windowName, HMENU hMenu) {
	this->m_hMenu = hMenu;
	
	HWND hWndParent;
	if (this->m_parent)
		hWndParent = this->m_parent->m_hWnd;
	else
		hWndParent = 0;
	
	this->m_hWnd = CreateWindowExA(this->m_dwExStyle, className, 
									windowName, this->m_dwStyle, 
									this->m_frame.x1, this->m_frame.y1, 
									this->m_frame.width(), this->m_frame.height(), 
									hWndParent, this->m_hMenu, 
									sysHInst, 0);

	if(windowName)
		this->setName((char *)windowName);
	else
		this->setName((char *)className);

	if (!strcmp(className, "DUIGenWin") || !strcmp(className, "DUIClearWin"))	
		SetWindowLong(this->m_hWnd, 0, (long)this);
}

void UIWindow::dockTop(int, RectArea&, RectArea&) {

}

void UIWindow::closeChildren() {

}

void UIWindow::initFrame(UIWindow*, int, int, int, bool) {

}

void UIWindow::sizeWindow(int, int, int) {

}

void UIWindow::updateMove(int, int) {

}
