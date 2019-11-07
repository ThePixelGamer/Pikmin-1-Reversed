#include <plugAtxServer.h>
#include <globals.h>
#include "../../__PLUG_SHARED/attachModule.h"

plugAtxServer::plugAtxServer()
{
    DarkGreen = CreateSolidBrush(0xC0C040);
    NormalGreen = CreateSolidBrush(0x40C040);
    LightBlue = CreateSolidBrush(0xE0E0FF);
    MistyRed = CreateSolidBrush(0xFFE0E0);
    hbr = CreateSolidBrush(0xC0C0C0);
    HighlightPen =  CreatePen(0, 1, GetSysColor(COLOR_3DHIGHLIGHT));
    h = CreatePen(0, 1, GetSysColor(COLOR_BTNSHADOW));
}

plugAtxServer::~plugAtxServer()
{

}

static plugAtxServer* GeneratePASInstance()
{
    return new plugAtxServer();
}

Object ObjectList[]
= {
    Object("AtxServer", true, &GeneratePASInstance),
    Object("AtxServerFile", false, nullptr),
    Object(0, false, nullptr),
};
