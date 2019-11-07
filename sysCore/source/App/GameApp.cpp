#include <App/GameApp.h>
#include <System/System.h>

GameApp::GameApp() {}

GameApp::~GameApp() {}

void GameApp::doInitApp() 
{
    int exstyle;
    int dwstyle;
    int unk1;
    int unk2;
    int width;
    int height;
    if (gsys->m_unkGameAppBool)
    {
        exstyle = 0x40000;
        dwstyle = 0x90000000;
        unk1 = 0;
        unk2 = 0;
        width = glnWidth;
        height = glnHeight;
    }
    else
    {
        exstyle = 0x40000;
        dwstyle = 0x80440000;
    }

	this->m_hasInit = false;
}

bool GameApp::idle()
{
    sysCurrWnd = this->m_mainWindow->m_hWnd;
    const int updateCode = this->idleUpdate();
    sysCurrWnd = nullptr;
    if (this->m_hasInit == false && !updateCode)
        return false;

    // invalidate heap.
    const int previousHeap = gsys->setHeap(-1);
    if (this->m_hasInit)
    {
        gsys->m_unkGameAppBool2 = true;
        SendMessage(this->m_mainWindow->m_hWnd, WM_CLOSE, 0, 0);
        gsys->m_unkGameAppBool2 = false;
        gsys->m_unkGameAppBool ^= 1;
        this->doInitApp();
        gsys->attachObjs();
        this->m_hasInit = false;
    }
    gsys->setHeap(previousHeap);
    return true;
}

void GameApp::renderall()
{
    this->m_mainWindow->update();
}