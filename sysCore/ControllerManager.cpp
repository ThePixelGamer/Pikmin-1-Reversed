// ControllerManager.cpp: implementation of the ControllerManager class.
//
//////////////////////////////////////////////////////////////////////

#include "ControllerManager.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ControllerMgr::ControllerMgr() {}

void ControllerMgr::update() { GetKeyboardState(this->lpKeyState); }

bool ControllerMgr::keyDown(int key) {
  return (this->lpKeyState[key] & 0x80) == 0x80;
}