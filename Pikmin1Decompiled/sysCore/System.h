#ifndef SYSTEM_H
#define SYSTEM_H

#include <cstdarg>
#include <algorithm>

#include "StdSystem.h"
class RandomAccessStream;
class UIWindow;
class BaseApp;
class AgeServer;
class AtxRouter;
class IDelegate2;

class SYSCORE_API System : public StdSystem {
public:
	System();
	System(const System&);
	~System();

	virtual RandomAccssStream* openFile(char*, bool, bool);
	virtual void 			   sndPlaySe(unsigned int);

	void				beginRender();
	void				buildModeList();
	UIWindow*			createDebugStream(UIWindow*);
	void				createFile(char*, bool);
	RandomAccessStream* doneRender();
	BaseApp*			firstApp();
	void				genAge(AgeServer*);
	AtxRouter*			getAtxRouter();
	int					getFrameCount();
	float				getFrameRate();
	float				getFrameTime();
	float 				getTime();
	void 				halt(char*, int, char*);
	void 				hardReset();
	int 				run(BaseApp*);
	void 				searchFiles(char*, char*, IDelegate2<char*, unsigned int>*, bool);
	void 				setAtxRouter(int);
	int 				setStreamType(int);
	bool 				setVideoMode(bool, int, int, int);
	void 				sleep(float);
	void 				updateSysClock();
	void 				waitRetrace();

	System operator=(const System&);
};

#endif

