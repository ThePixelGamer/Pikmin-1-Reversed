#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef SYSTEM_H
#define SYSTEM_H

#include "StdSystem.h"
#include "../UI/UI.h"
#include "../BaseApp.h"
#include "../IDelegate.h"
#include "../Atx/AtxRouter.h"

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

class DebugStream : public Stream // not exported
{
public:
	//0h - vtbl
	//4h - stream var
	int m_written; //8h
	int m_dwordC; //Ch
	char m_unk[256]; //10h
	RandomAccessStream* m_RAStream; // 110h
	UIWindow* m_window; //114h

	DebugStream(UIWindow* window) {
		this->m_written = 0;
		this->m_dwordC = 0;

		this->m_window = new UIWindow(window, 15, 0x50200140, 512, 0);
		this->m_window->sizeWindow(window->m_client.width(), window->m_client.height(), 0);
		this->m_window->createWindow("ListBox", 0, 0);
		WPARAM obj = (WPARAM)GetStockObject(DEFAULT_GUI_FONT);
		SendMessage(this->m_window->m_hWnd, 0x30, obj, 0);
		this->m_RAStream = gsys->createFile("../log.txt", true);
	}

	void writeChar(char toWrite) { // unsure of name
		if (this->m_written >= 255) {
			this->flush();
		}
		this->m_unk[this->m_written] = toWrite;
		this->m_written++;

	}

	virtual void write(void* buf, int len) {
		for (int i = 0; i < len; ++i) {
			char currentChar = *((char*)buf + i);
			if (currentChar == '\n') {
				this->flush();
			}
			else if (currentChar == '\t') {
				this->writeChar(' ');
				this->writeChar(' ');
			}
			else {
				this->writeChar(currentChar);
			}
		}
	}

	virtual void flush() {
		this->m_unk[this->m_written] = 0;
		if (this->m_window) {
			if (gsys->m_debugStreamUnk) {
				SendMessage(this->m_window->m_hWnd, 0x180, 0, (LPARAM)this->m_unk);
				SendMessage(this->m_window->m_hWnd, 0x186, this->m_dwordC++, 0);

				if (this->m_RAStream) { // has file open
					char newline[2];
					strcpy(newline, "\n");
					this->m_RAStream->write(this->m_unk, strlen(this->m_unk));
					this->m_RAStream->write(newline, strlen(newline));
				}
			}
		}
		this->m_written = 0;
	}
};

#endif

