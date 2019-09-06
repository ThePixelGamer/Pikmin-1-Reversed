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

void UIWINDOWPRINT(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	char dest[1024];

	if(sysCon) {
		if ("uiWindow")
			sysCon->print("%s: ", "uiWindow");
		vsprintf(dest, fmt, args);
		if(strlen(dest)) {
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

UIWindow::UIWindow(UIWindow * parent, int unk2, int style, int exstyle, bool unk5) : UIFrame() {
	this->m_unk7 = 0;
	this->m_unk10 = 0;
	this->m_hMenu = 0; //HMENU
	initFrame(parent, unk2, style, exstyle, unk5);
}

UIWindow::~UIWindow() {
	UIWINDOWPRINT("now closing window %s", this->name);
}

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

void UIWindow::activate() {

}

int UIWindow::processMessage(HWND hWnd, unsigned int Msg, WPARAM wParam, long lParam) {
	switch (Msg)
	{
	case WM_MOVE: 
		{
			UIWindow* windLong = (UIWindow*)GetWindowLongA(hWnd, 0);
			if (windLong)
				windLong->updateMove(lParam, lParam >> 16);
			return 0;
		}
	case WM_SIZE:
		{
			UIWindow* windLong = (UIWindow*)GetWindowLongA(hWnd, 0);
			if (windLong)
				windLong->updateSizes(lParam, lParam >> 16);
			return 0;
		}
	case WM_CLOSE:
		{
			UIWindow* windLong = (UIWindow*)GetWindowLongA(hWnd, 0);
			if(windLong)
			{
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

LRESULT UIWindow::returnMessage(HWND hWnd, unsigned int Msg, WPARAM wParam, long lParam) {
	return DefWindowProc(hWnd, (UINT)Msg, wParam, lParam);
}

HDWP UIWindow::resizeChildren(HDWP hWinPosInfo, RectArea & rect) {
	for (CoreNode* i = Child(); i; i = i->Next()) {
		hWinPosInfo = this->resizeFrame(hWinPosInfo, rect);
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
									sysHInst, NULL);

	if (windowName)
		this->setName((char*)windowName);
	else
		this->setName((char*)className);

	if (!strcmp(className, "DUIGenWin") || !strcmp(className, "DUIClearWin"))
		SetWindowLong(this->m_hWnd, 0, (long)this);
}

void UIWindow::dockTop(int _height, RectArea& old, RectArea& newarea) {
	old.y1 = newarea.y1;
	int newY2 = (_height < newarea.height()) ? _height : newarea.height();
	old.y2 = newY2 + old.y1;
	newarea.y1 = old.y2;
}

void UIWindow::closeChildren() { // asm matches
	UIWindow* childNext;
	for (UIWindow* child = (UIWindow*)this->Child(); child; child = childNext)
	{
		childNext = (UIWindow*)child->Next();
		SendMessage(child->m_hWnd, WM_CLOSE, 0, 0);
	} 
}

void UIWindow::initFrame(UIWindow * parent, int a2, int style, int exstyle, bool a5) {
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
		this->m_zero.y1 -= GetSystemMetrics(SM_CYMENU);//     The height of a single-line menu bar, in pixels.
	if (this->m_dwStyle & WS_VSCROLL)
		this->m_zero.x2 += GetSystemMetrics(SM_CXVSCROLL);// The width of a vertical scroll bar, in pixels.
	if (this->m_dwStyle & WS_HSCROLL)
		this->m_zero.y2 += GetSystemMetrics(SM_CYHSCROLL);// The height of a horizontal scroll bar, in pixels.

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
	if(a2) {
		RectArea rect;
		if(m_dwStyle & 0x40000000) {
			rect.x1 = this->m_parent->m_client.x1;
			rect.y1 = this->m_parent->m_client.y1;
			rect.x2 = this->m_parent->m_client.x2;
			rect.y2 = this->m_parent->m_client.y2;
		}
		else {
			SystemParametersInfoA(SPI_GETWORKAREA, 0, &rect, 0);
		}

		w = rect.width() / 2 + rect.x1 - this->m_unk8 / 2;
		h = rect.height() / 2 + rect.y1 - this->m_unk9 / 2;

		if(w < 0)
			w = 0;
		if(h < 0)
			h = 0;
		if(this->m_unk8 > rect.width())
			this->m_unk8 = rect.width();
		if(this->m_unk9 > rect.height())
			this->m_unk9 = rect.height();
	}
	else {
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

//////////////////////////////////////////////////////////////////////
// ToolWindow class functions
//////////////////////////////////////////////////////////////////////

ToolWindow::ToolWindow(UIWindow * parent, int unk2, int style, int exstyle, bool unk5) 
	: UIWindow(parent, unk2, style, exstyle, unk5) {}

void ToolWindow::createWindow(LPCSTR className, LPCSTR windowName, HMENU hMenu) {
	UIWindow::createWindow(className, windowName, hMenu);

	this->m_toolWindow = new UIWindow(this, 15, 0x52000340, 0, 0);
	this->m_toolWindow->sizeWindow(this->m_unk8, this->m_unk9, 0);
	this->m_toolWindow->createWindow("ToolbarWindow32", "toolbar", NULL);
}

void ToolWindow::initTools(HINSTANCE inst, int tickFreq, TBBUTTON* unkBut, tagTBADDBITMAP* unkMap) {
	this->m_unk11 = inst;
	HBITMAP bitMap = LoadBitmap(inst, (const char*)unkMap->nID);
	LPARAM param = NULL;
	SendMessage(this->m_toolWindow->m_hWnd, TBM_GETTOOLTIPS, 0x14, 0);
	SendMessage(this->m_toolWindow->m_hWnd, TBM_SETBUDDY, 0, 0x190019);
	SendMessage(this->m_toolWindow->m_hWnd, TBM_CLEARSEL, tickFreq, param);
	SendMessage(this->m_toolWindow->m_hWnd, TBM_SETTICFREQ, tickFreq, (LPARAM)unkBut);
	SendMessage(this->m_toolWindow->m_hWnd, TBM_GETBUDDY, 0, 0);
}

int ToolWindow::processMessage(HWND hWnd, unsigned int Msg, WPARAM wParam, long lParam) {
	if (Msg == WM_NOTIFY && ((tagNMTTDISPINFOA*)lParam)->hdr.code == TTN_NEEDTEXT)
	{
		char buffer[512];
		LoadString(this->m_unk11, ((tagNMTTDISPINFOA*)lParam)->hdr.idFrom, buffer, FORMAT_MESSAGE_ALLOCATE_BUFFER);
		sprintf(((tagNMTTDISPINFOA*)lParam)->lpszText, buffer);
	}
	return UIWindow::processMessage(hWnd, Msg, wParam, lParam);
}

//////////////////////////////////////////////////////////////////////
// ComboBox class functions
//////////////////////////////////////////////////////////////////////

ComboBox::ComboBox(UIWindow * parent, int unk2, int style, int exstyle, bool unk5) : UIWindow(parent, unk2, style, exstyle, unk5) {
	this->m_boxExStyle = WM_CHAR;
}

void ComboBox::addOption(char* option, bool unsure) {
	SendMessage(this->m_boxWindow->m_hWnd, CB_ADDSTRING, 0, (LPARAM)option);

	LRESULT foundString = SendMessage(this->m_boxWindow->m_hWnd, LB_FINDSTRINGEXACT, NULL, (LPARAM)option);
	if (foundString != -1)
		this->selOption(foundString);
}

void ComboBox::selOption(int option) {
	SendMessage(this->m_boxWindow->m_hWnd, CB_SETCURSEL, option, NULL);
}

int ComboBox::processMessage(HWND hWnd, unsigned int Msg, WPARAM wParam, long lParam) {
	if (wParam == WM_USER) {
		SendMessage(this->m_boxWindow->m_hWnd, WM_GETTEXT, sizeof(cBoxStringBuf), (LPARAM)cBoxStringBuf); 
		this->entryHandler(cBoxStringBuf);

		LRESULT foundString = SendMessage(this->m_boxWindow->m_hWnd, CB_FINDSTRINGEXACT, 0xFFFFFFFF, (LPARAM)cBoxStringBuf);
		if (foundString == -1)
			SendMessage(this->m_boxWindow->m_hWnd, CB_ADDSTRING, 0, (LPARAM)cBoxStringBuf);
	}
	return UIWindow::processMessage(hWnd, Msg, wParam, lParam);
}

void ComboBox::entryHandler(char*) { }

LRESULT ComboBox_WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	switch (Msg) 
	{
	case WM_SETFOCUS:
		::hWnd = GetParent(GetParent(hWnd));
		break;
	case WM_KILLFOCUS:
		PostMessage(::hWnd, WM_USER, 0, 0);
		break;
	case WM_KEYDOWN:
		if (wParam == WM_GETTEXT)
			PostMessage(::hWnd, WM_USER, 0, 0);
		break;

	}

	return CallWindowProcA(lpPrevWndFunc,hWnd, Msg, wParam, lParam);
}

void ComboBox::createWindow(LPCSTR className, LPCSTR windowName, HMENU hMenu) {
	UIWindow::createWindow(className, windowName, hMenu);

	/*Create ComboBox window, and resize window based on client.width*/
	this->m_boxWindow = new UIWindow(this, 15, this->m_boxExStyle | 0x50200000, NULL, NULL);
	this->m_boxWindow->sizeWindow((this->m_client.width()) - 16, 150, 0);
	this->m_boxWindow->createWindow("ComboBox",0 ,0);

	/*Set the font to the default GUI font for Windows*/
	WPARAM font = (WPARAM)GetStockObject(DEFAULT_GUI_FONT);
	SendMessage(this->m_boxWindow->m_hWnd, WM_SETFONT, font, NULL);

	POINT unk;
	unk.y = 4;
	unk.x = 4;

	::hWnd = this->m_hWnd;

	HWND window = ChildWindowFromPoint(this->m_boxWindow->m_hWnd, unk);
	::lpPrevWndFunc = (WNDPROC)SetWindowLong(window, -4, (LPARAM)ComboBox_WndProc);
}

//////////////////////////////////////////////////////////////////////
// EditBox class functions
//////////////////////////////////////////////////////////////////////

EditBox::EditBox(UIWindow * parent, int unk2, int style, int exstyle, bool unk5) 
	: ComboBox(parent, unk2, style, exstyle, unk5) {
	this->m_boxExStyle = 0x41;
}

void EditBox::entryHandler(char* msg) {
	UIWINDOWPRINT("got new text %s\n", msg);
	UIWINDOWPRINT("sending message to %s\n", this->m_parent->name);
	SendMessage(this->m_parent->m_hWnd, WM_USER, 0, (LPARAM)msg);
}

int EditBox::processMessage(HWND hWnd, unsigned int Msg, WPARAM wParam, long lParam) {
	if (Msg == WM_COMMAND && lParam >> 16 == 1) {
		LRESULT ret = SendMessage(this->m_boxWindow->m_hWnd, CB_GETCURSEL, 0, 0);
		SendMessage(this->m_boxWindow->m_hWnd, CB_GETLBTEXT, ret, (LPARAM)eBoxStringBuf);
		PostMessage(this->m_parent->m_hWnd, WM_USER, 0, (LPARAM)eBoxStringBuf);
	}
	return ComboBox::processMessage(hWnd, Msg, wParam, lParam);
}

//////////////////////////////////////////////////////////////////////
// OptionBox class functions
//////////////////////////////////////////////////////////////////////

OptionBox::OptionBox(UIWindow * parent, int unk2, int style, int exstyle, bool unk5) 
	: ComboBox(parent, unk2, style, exstyle, unk5) {
	this->m_boxExStyle = 0x3;
}

int OptionBox::processMessage(HWND hWnd, unsigned int Msg, WPARAM wParam, long lParam) {
	if (Msg == WM_COMMAND) {
		UINT wParamShifted = wParam >> 16;
		if (wParam >> 16 == 1) {
			LRESULT selChange = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
			UIWINDOWPRINT("got selection change %d, %08x\n", lParam, selChange);
			this->selectionChanged(selChange);
		}
		else if (wParamShifted == 5)
			UIWINDOWPRINT("got edit change\n");
	}
	return ComboBox::processMessage(hWnd, Msg, wParam, lParam);
}

void OptionBox::selectionChanged(int) { } // empty vFunction

//////////////////////////////////////////////////////////////////////
// UIMgr class functions
//////////////////////////////////////////////////////////////////////

SYSCORE_API UIMgr* uiMgr;

UIMgr::UIMgr() : Node("UIMgr"), m_unk1("<Node>") {
	this->RegisterGenWindowClass("DUIGenWin", 0, true);
	this->RegisterGenWindowClass("DUIClearWin", 0, false);
	InitCommonControls();
	nodeMgr->firstNode()->add(this);
}

UIMgr::~UIMgr() {

}

#include "../System/System.h"

LRESULT __stdcall selectWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	UINT msg = Msg;
	if (Msg == 1)
	{
		SetWindowLongA(hWnd, 0, 0);
		goto RETURNNOW;
	}
	if (msg == 2)
	{
		nodeMgr->Del((Node*)GetWindowLongA(hWnd, 0));
	RETURNNOW:
		UIWindow* wind = (UIWindow*)GetWindowLongA(hWnd, 0);
		if (!wind || gsys->isShutdown())
			return DefWindowProcA(hWnd, Msg, wParam, lParam);
		else
			return wind->processMessage(hWnd, Msg, wParam, lParam);
	}
	if (Msg != 28)
		goto RETURNNOW;
	if (wParam)
	{
		if (!gsys->isShutdown() && !gsys->isActive())
		{
			gsys->setActive(1);
			if (uiMgr)
			{
				uiMgr->activateWindow(hWnd, (UIWindow*)GetWindowLongA(hWnd, 0));
			}
		}
	}
	else if (gsys->isActive())
	{
		gsys->setActive(0);
	}
	return 0;
}

void UIMgr::RegisterGenWindowClass(LPCSTR lpszClass, void* wndProcAddr, bool a3)
{
	tagWNDCLASSEXA wcx;
	LRESULT(__stdcall * wndProc)(HWND, UINT, WPARAM, LPARAM);

	if (!GetClassInfoExA(sysHInst, lpszClass, &wcx))
	{
		wcx.cbSize = 48;
		wcx.lpszClassName = lpszClass;
		wcx.hInstance = sysHInst;
		if (a3)
			wndProc = (LRESULT(__stdcall*)(HWND, UINT, WPARAM, LPARAM))wndProcAddr;
		else
			wndProc = selectWndProc;
		wcx.lpfnWndProc = wndProc;
		wcx.hCursor = LoadCursorA(0, IDC_ARROW);
		wcx.hIcon = LoadIconA(hInstance, IDI_APPLICATION); // originally 0x65 instead of IDI_APPLICATION
		wcx.lpszMenuName = 0;
		wcx.hbrBackground = (HBRUSH)(a3 != 0 ? COLOR_BTNSHADOW : COLOR_SCROLLBAR);
		wcx.style = 32;
		wcx.cbClsExtra = 0;
		wcx.cbWndExtra = 4;
		wcx.hIconSm = LoadIconA(hInstance, IDI_APPLICATION); // originally 0x65 instead of IDI_APPLICATION
		RegisterClassExA(&wcx);
	}
}

void UIMgr::activateWindow(HWND hWnd, UIWindow * window)
{
	for (CoreNode* i = this->child; i; i = i->next)
		((UIWindow*) i)->activate();
}

bool UIMgr::isActive()
{
	bool retVal = false;

	for (UIWindow* i = (UIWindow*)this->Child(); i; i = (UIWindow*)i->Next())
	{
		if (i->m_dwExStyle & WS_EX_APPWINDOW)
			retVal = true;

	}
	return retVal;
}