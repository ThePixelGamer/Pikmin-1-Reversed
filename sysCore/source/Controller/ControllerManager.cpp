#include <Controller/ControllerManager.h>

ControllerMgr::ControllerMgr() {}

void ControllerMgr::update() { GetKeyboardState(this->lpKeyState); }

bool ControllerMgr::keyDown(int key) { return (this->lpKeyState[key] & 0x80) == 0x80; }

void ControllerMgr::updateController(class Controller* cont) { unsigned __int32 controllerVal; }