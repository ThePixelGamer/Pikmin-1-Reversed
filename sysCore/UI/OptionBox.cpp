#include "OptionBox.h"

OptionBox::OptionBox(UIWindow* parent, int unk2, int style, int exstyle, bool unk5)
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
		{
			UIWINDOWPRINT("got edit change\n");
		}
	}
	return ComboBox::processMessage(hWnd, Msg, wParam, lParam);
}

void OptionBox::selectionChanged(int) { } // empty vFunction