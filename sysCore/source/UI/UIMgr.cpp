#include <System/System.h>
#include <UI/UIMgr.h>

SYSCORE_API UIMgr* uiMgr;

UIMgr::UIMgr() : Node("UIMgr"), m_unk1("<Node>")
{
    this->RegisterGenWindowClass("DUIGenWin", 0, true);
    this->RegisterGenWindowClass("DUIClearWin", 0, false);
    InitCommonControls();
    nodeMgr->firstNode()->add(this);
}

UIMgr::~UIMgr() {}

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
        wcx.hIcon = LoadIconA(hInstance,
                              IDI_APPLICATION); // originally 0x65 instead of IDI_APPLICATION
        wcx.lpszMenuName = 0;
        wcx.hbrBackground = (HBRUSH)(a3 != 0 ? COLOR_BTNSHADOW : COLOR_SCROLLBAR);
        wcx.style = 32;
        wcx.cbClsExtra = 0;
        wcx.cbWndExtra = 4;
        wcx.hIconSm = LoadIconA(hInstance,
                                IDI_APPLICATION); // originally 0x65 instead of IDI_APPLICATION
        RegisterClassExA(&wcx);
    }
}

void UIMgr::activateWindow(HWND hWnd, UIWindow* window)
{
    for (CoreNode* i = this->child; i; i = i->next)
        ((UIWindow*)i)->activate();
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
