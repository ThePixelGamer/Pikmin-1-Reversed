#include <UI/ComboBox.h>

ComboBox::ComboBox(UIWindow* parent, int unk2, int style, int exstyle, bool unk5)
        : UIWindow(parent, unk2, style, exstyle, unk5)
{
    this->m_boxExStyle = WM_CHAR;
}

void ComboBox::addOption(char* option, bool unsure)
{
    SendMessage(this->m_boxWindow->m_hWnd, CB_ADDSTRING, 0, (LPARAM)option);

    LRESULT foundString = SendMessage(this->m_boxWindow->m_hWnd, LB_FINDSTRINGEXACT, NULL, (LPARAM)option);
    if (foundString != -1)
        this->selOption(foundString);
}

void ComboBox::selOption(int option) { SendMessage(this->m_boxWindow->m_hWnd, CB_SETCURSEL, option, NULL); }

int ComboBox::processMessage(HWND hWnd, unsigned int Msg, WPARAM wParam, long lParam)
{
    unsigned int msg = Msg;
    if (wParam == WM_USER)
    {
        SendMessage(this->m_boxWindow->m_hWnd, WM_GETTEXT, sizeof(cBoxStringBuf), (LPARAM)cBoxStringBuf);
        this->entryHandler(cBoxStringBuf);

        LRESULT foundString =
            SendMessage(this->m_boxWindow->m_hWnd, CB_FINDSTRINGEXACT, 0xFFFFFFFF, (LPARAM)cBoxStringBuf);
        if (foundString == -1)
            SendMessage(this->m_boxWindow->m_hWnd, CB_ADDSTRING, 0, (LPARAM)cBoxStringBuf);
    }
    return UIWindow::processMessage(hWnd, Msg, wParam, lParam);
}

void ComboBox::entryHandler(char*) {}

LRESULT ComboBox_WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
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

    return CallWindowProcA(lpPrevWndFunc, hWnd, Msg, wParam, lParam);
}

void ComboBox::createWindow(LPCSTR className, LPCSTR windowName, HMENU hMenu)
{
    UIWindow::createWindow(className, windowName, hMenu);

    /*Create ComboBox window, and resize window based on client.width*/
    this->m_boxWindow = new UIWindow(this, 15, this->m_boxExStyle | 0x50200000, NULL, NULL);
    this->m_boxWindow->sizeWindow((this->m_client.width()) - 16, 150, 0);
    this->m_boxWindow->createWindow("ComboBox", 0, 0);

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