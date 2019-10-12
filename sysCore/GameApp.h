#ifndef GAMEAPP_H
#define GAMEAPP_H
#include "BaseApp.h"
#include "UI/UIWindow.h"

class GameApp : public BaseApp {
public:
  UIWindow *m_mainWindow; // 54h
  bool unkByte;           // 58h

  GameApp();
  virtual ~GameApp();

  virtual bool idle();

  void doInitApp();
};

#endif
