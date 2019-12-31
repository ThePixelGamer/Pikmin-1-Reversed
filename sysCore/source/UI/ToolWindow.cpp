#include <UI/ToolWindow.h>

ToolWindow::ToolWindow(UIWindow* parent, int unk2, int style, int exstyle, bool unk5)
        : UIWindow(parent, unk2, style, exstyle, unk5)
{
}

void ToolWindow::createWindow(LPCSTR className, LPCSTR windowName, HMENU hMenu)
{
    UIWindow::createWindow(className, windowName, hMenu);

    this->m_pWindow = new UIWindow(this, 15, 0x52000340, 0, 0);
    this->m_pWindow->sizeWindow(this->m_width, this->m_height, 0);
    this->m_pWindow->createWindow("ToolbarWindow32", "toolbar", NULL);
}

void ToolWindow::initTools(HINSTANCE wind, int tickFreq, TBBUTTON* unkBut, tagTBADDBITMAP* unkMap)
{
    this->m_tWindowInst = wind;
    HBITMAP bitMap = LoadBitmap(wind, (const char*)unkMap->nID);
    LPARAM param = NULL;
    SendMessage(this->m_pWindow->m_hWnd, TBM_GETTOOLTIPS, 0x14, 0);
    SendMessage(this->m_pWindow->m_hWnd, TBM_SETBUDDY, 0, 0x190019);
    SendMessage(this->m_pWindow->m_hWnd, TBM_CLEARSEL, tickFreq, param);
    SendMessage(this->m_pWindow->m_hWnd, TBM_SETTICFREQ, tickFreq, (LPARAM)unkBut);
    SendMessage(this->m_pWindow->m_hWnd, TBM_GETBUDDY, 0, 0);
}

int ToolWindow::processMessage(HWND hWnd, unsigned int Msg, WPARAM wParam, long lParam)
{
    if (Msg == WM_NOTIFY && ((NMTTDISPINFOA*)lParam)->hdr.code == TTN_NEEDTEXT)
    {
        char buffer[512];
        LoadString(this->m_tWindowInst, ((NMTTDISPINFOA*)lParam)->hdr.idFrom, buffer, FORMAT_MESSAGE_ALLOCATE_BUFFER);
        sprintf(((NMTTDISPINFOA*)lParam)->lpszText, buffer);
    }
    return UIWindow::processMessage(hWnd, Msg, wParam, lParam);
}
