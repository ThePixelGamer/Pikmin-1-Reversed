#include <UI/AppWindow.h>
#include <System/System.h>

int AppWindow::processMessage(HWND hWnd, unsigned int Msg, WPARAM wParam, long lParam)
{
    unsigned int msg = Msg;
    if (Msg == WM_CLOSE && !gsys->m_unkGameAppBool2)
    {
        // TODO   
    }
    return UIWindow::processMessage(hWnd, Msg, wParam, lParam);
}