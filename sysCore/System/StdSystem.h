#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#include <cstdarg>
#include <algorithm>
#include <Windows.h>
#include "../Stream/RandomAccessStream.h"

#ifndef FRAS
#define FRAS

class FileRandomAccessStream : public RandomAccessStream {
public:
	// 0h - vtable
	//(Stream: 4h)
	FILE* fStream; // 8h
	int dwordC; // Ch
	int fileSize; // 10h 

	FileRandomAccessStream(FILE* fpointer, char* cwd);
	virtual int getPosition();
};

#endif

#ifndef STDSYSTEM_H
#define STDSYSTEM_H

class CacheTexture;
class LoadIdler;
class AnimData;
class GfxobjInfo;
class Texture;
class Graphics;
class AyuHeap;
class LFInfo;
class Shape;
class LFlareGroup;

class SYSCORE_API StdSystem {
public:
	bool pending;	//4h
	double fade;	//8h this + 8

	char* baseDir;	//50h

	char* bloRoot;  //48h this + 72
	char* texRoot;  //4Ch this + 76

	char* dataRoot;	//54h this + 84
	int unkShutdownCode; //1C8h this + 456

	StdSystem();

	virtual void					initSoftReset();
	virtual RandomAccessStream* openFile(char*, bool, bool);
	virtual void					copyRamToCache(unsigned int, unsigned int, unsigned int);
	virtual void					copyCacheToRam(unsigned int, unsigned int, unsigned int);
	virtual void					copyWaitUntilDone();
	virtual void					copyCacheToTexture(CacheTexture*);
	virtual void					Activate(bool);
	virtual void					parseArchiveDirectory(char*, char*);
	virtual void					sndPlaySe(unsigned int) = 0;
	virtual void					startLoading(LoadIdler*, bool, unsigned int);
	virtual void					endLoading();

	bool							isShutdown();
	bool							isActive() { return (this->unkShutdownCode & 0x200000) == 0x200000; }
	void							setActive(bool set) { }
	double							getHalfRand(float a);
	double							getRand(float a);
	bool							resetPending();
	void							set2DRoot(char* _bloroot, char* _texroot);
	
	/*
		void		 Shutdown();
		void		 addAnimation(AnimData*, char*);
		void		 addGfxObject(GfxobjInfo*);
		void		 addTexture(Texture*, char*);
		void		 ageAnyAnimations();
		void		 attachObjs();
		void		 detachObjs();
		AnimData*	 findAnimation(char*);
		AnimData*	 findAnyAnimation(char*);
		GfxobjInfo*	 findAnyGfxObject(char*, unsigned int);
		int			 findAnyIndex(char*, char*);
		GfxobjInfo*	 findGfxObject(char*, unsigned int);
		AnimData*	 findIndexAnimation(char*, int);
		GfxobjInfo*	 findTexture(Texture*);
		void		 flushLFlares(Graphics*);
		void		 genAge(AgeServer*);
		void		 getAppMemory(char*);
		float		 getFade();
		float		 getHalfRand(float);
		AyuHeap*	 getHeap(int);
		int			 getHeapNum();
		LFInfo*		 getLFlareInfo();
		double		 getRand(float);
		Shape*		 getShape(char*, char*, char*, bool);
		void		 initLFlares(int);
		void		 invalidateObjs(unsigned int, unsigned int);
		bool		 isActive();
		AnimData*	 loadAnimation(Shape*, char*, bool);
		void		 loadBundle(char*, bool);
		Shape*		 loadShape(char*, bool);
		Texture*	 loadTexture(char*, bool);
		void		 onceInit();
		void		 parseArchiveDirectory(char*, char*);
		LFlareGroup* registerLFlare(Texture*);
		void		 resetHeap(int, int);
		void		 resetLFlares();
		void		 resetPending();
		void		 set2DRoot(char*, char*);
		void		 setActive(bool);
		void		 setDataRoot(char*);
		void		 setFade(float, float);
		void		 setFrameClamp(int);
		void		 setHeap(int);
		void		 setTextureBase(char*, char*);
		void		 softReset();*/
		static char* stringDup(char*);

		//StdSystem operator=(const StdSystem&);
};

#endif