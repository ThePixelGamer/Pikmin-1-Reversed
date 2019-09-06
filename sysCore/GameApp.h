#ifndef GAMEAPP_H
#define GAMEAPP_H
#include "BaseApp.h"
#include "UI/UI.h"

class GameApp :
	public BaseApp
{
public:
	UIWindow* m_mainWindow; // 54h
	bool unkByte; //58h

	GameApp();
	~GameApp();

	virtual void InitApp();
};

#endif