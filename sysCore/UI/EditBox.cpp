#include "EditBox.h"

EditBox::EditBox(UIWindow* parent, int unk2, int style, int exstyle, bool unk5)
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