#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef SYSTEM_H
#define SYSTEM_H

#include "StdSystem.h"
#include "../UI/UIMgr.h"
#include "../BaseApp.h"
#include "../IDelegate.h"
#include "../Atx/AtxRouter.h"
#include "../Networking/WSocket.h"
#include "../Stream/DebugStream.h"

class SYSCORE_API System : public StdSystem {
public:
	//(StdSystem: 4h-240h)
	/* current unknown members
		void* unk; // 244h
		void* unk; // 248h
		bool  unk; // 24Ch
		bool  unk; // 24Dh
		bool  unk; // 24Eh
		void* unk; // 250h
		void* unk; // 254h
		void* unk; // 258h
		void* unk; // 25Ch
		void* unk; // 260h
		AtxFileStream unk; // 264h
		BufferedStream unk; // 284h
	*/
	int streamType;	  // 2B0h
	//ControllerMgr controllerMgr; // 2B0h
	char m3B8h[128]; // 3B8h
	AtxRouter* mainRouter; // 438h
	/* current unknown members
		void* unk; // 440h
		void* unk; // 444h
		void* unk; // 448h
		void* unk; // 44Ch
		void* unk; // 450h
		void* unk; // 454h
	*/
	double frameTime; // 458h
	//void* unk; // 45Ch
	double frameRate; // 460h
	int frameCount;   // 464h
	//void* unk; // 468h

	System();
	System(const System&);
	~System();

	virtual RandomAccessStream* openFile(char*, bool);
	//virtual void 			parseArchiveDirectory(char * );
	virtual void 			sndPlaySe(unsigned int);

	void					beginRender();
	void					buildModeList();
	UIWindow*				createDebugStream(UIWindow*);
	RandomAccessStream	*	createFile(char*, bool);
	void					doneRender();
	BaseApp*				firstApp();

	virtual void			genAge(AgeServer&);
	AtxRouter*				getAtxRouter();
	int						getFrameCount();
	float					getFrameRate();
	float					getFrameTime();
	float 					getTime();
	static void 			halt(char*, int, char*);
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

extern SYSCORE_API System* gsys;
#endif

