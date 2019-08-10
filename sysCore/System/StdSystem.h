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

#include "../AgeServer.h"
#include "../Nodes.h"

class CacheTexture;
class LoadIdler;
class AnimData;
class Texture;
class Graphics;
class AyuHeap;
class LFInfo;
class Shape;
class LFlareGroup;

struct ID32 {
	//0h - 8h
};

struct GfxobjInfo { //used elsewhere
	//vtable - 0h
	int unk1; //4h
	int unk2; //8h
	char* str; //Ch
	ID32 unk3; //10h
	int unk4; //1Ch

	void insertAfter(GfxobjInfo* a2) {}
};

class SYSCORE_API StdSystem {
public:
	/* current unknown members
		void* unk; // 4h
		void* unk; // 8h
		void* unk; // Ch
		void* unk; // 10h
		void* unk; // 14h
		void* unk; // 18h
		void* unk; // 1Ch
		void* unk; // 20h
		void* unk; // 24h
		void* unk; // 28h
		void* unk; // 2Ch
		void* unk; // 30h
		void* unk; // 34h
		void* unk; // 38h
		void* unk; // 3Ch
		void* unk; // 40h
		void* unk; // 44h
		void* unk; // 48h
		void* unk; // 4Ch	
	*/
	char* baseDir; // 50h
	char* fileName;	 // 54h
	/* current unknown members
		char unk[8][40]; //58h (known but not sure about type)
		void* unk; // 198h
		void* unk; // 19Ch
		void* unk; // 1A0h
		void* unk; // 1A4h
		void* unk; // 1A8h
		void* unk; // 1ACh
		void* unk; // 1B0h
		void* unk; // 1B4h
		void* unk; // 1B8h
		void* unk; // 1BCh
		void* unk; // 1C0h
		void* unk; // 1C4h
		void* unk; // 1C8h
	*/
	int unkShutdownCode; // 1C8h
	/* current unknown members
		void* unk; // 1CCh
	*/
	GfxobjInfo gfx; // 1D0h
	int unkBool; // 1F0h
	/* current unknown members
		void* unk; // 1F4h
		void* unk; // 1F8h
		void* unk; // 1FCh
	*/
	CoreNode core1; // 200h
	CoreNode core2; // 214h
	/* current unknown members
		void* unk; // 228h
		void* unk; // 22Ch
		void* unk; // 230h
		void* unk; // 234h
		void* unk; // 238h
		void* unk; // 23Ch
		void* unk; // 240h	
	*/

	StdSystem();

	virtual void				initSoftReset();
	virtual RandomAccessStream* openFile(char*, bool, bool);
	virtual void				copyRamToCache(unsigned int, unsigned int, unsigned int);
	virtual void				copyCacheToRam(unsigned int, unsigned int, unsigned int);
	virtual void				copyWaitUntilDone();
	virtual void				copyCacheToTexture(CacheTexture*);
	virtual void				Activate(bool);
	virtual void				parseArchiveDirectory(char*, char*);
	virtual void				sndPlaySe(unsigned int) = 0;
	virtual void				startLoading(LoadIdler*, bool, unsigned int);
	virtual void				endLoading();

	void		 Shutdown();
	void		 addAnimation(AnimData*, char*);
	void		 addGfxObject(GfxobjInfo*);
	void		 addTexture(Texture*, char*);
	void		 ageAnyAnimations();
	void		 attachObjs();
	void		 detachObjs();
	AnimData*	 findAnimation(char*);
	AnimData*	 findAnyAnimation(char*);
	GfxobjInfo*  findAnyGfxObject(char*, unsigned int);
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
	bool		 isShutdown();
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
	void		 softReset();
	static char* stringDup(char*);

		//StdSystem operator=(const StdSystem&);
};

#endif