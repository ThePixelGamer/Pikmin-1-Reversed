#ifndef SYSTEM_H
#define SYSTEM_H

#include "StdSystem.h"

class UIWindow { public: UIWindow() {} };
class BaseApp { public: BaseApp() {} };
class AgeServer { public: AgeServer() {} };
class AtxRouter { public: AtxRouter() {} };
class IDelegate2 { public: IDelegate2() {} };

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

class SYSCORE_API System : public StdSystem {
public:
	char * currentWorkingDirectory; // this + 80
	char * fileName; // ??? this + 84
	int streamType;	  // this + 688
	double frameTime; // this + 1112
	double frameRate; // this + 1116
	int frameCount;   // this + 1128

	System();
	System(const System&);
	~System();

	virtual FileRandomAccessStream* openFile(char*, bool, bool);
	//virtual void 			parseArchiveDirectory(char * );
	virtual void 			sndPlaySe(unsigned int);

	void					beginRender();
	void					buildModeList();
	UIWindow*				createDebugStream(UIWindow*);
	FileRandomAccessStream*	createFile(char*, bool);
	void					doneRender();
	BaseApp*				firstApp();
	void					genAge(AgeServer*);
	AtxRouter*				getAtxRouter();
	int						getFrameCount();
	float					getFrameRate();
	float					getFrameTime();
	float 					getTime();
	void 					halt(char*, int, char*);
	void 					hardReset();
	int 					run(BaseApp*);
	//void 					searchFiles(char*, char*, IDelegate2<char*, unsigned int>*, bool);
	void 					setAtxRouter(int);
	int 					setStreamType(int);
	bool 					setVideoMode(bool, int, int, int);
	void 					sleep(float);
	void 					updateSysClock();
	void 					waitRetrace();
};

SYSCORE_API System * gsys;

#endif

