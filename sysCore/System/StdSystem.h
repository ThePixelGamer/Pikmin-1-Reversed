#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif


#ifndef STDSYSTEM_H
#define STDSYSTEM_H

#include <Windows.h>
#include "../AgeServer.h"
#include "../Nodes/Node.h"
#include "../ObjInfo.h"
#include "../AyuHeap.h"
#include "../Stream/FileIO.h"

#include <cstdarg>
#include <algorithm>

class CacheTexture;
class LoadIdler;
class AnimData;
class Texture;
class Graphics;
class AyuHeap;
class LFInfo;
class Shape;
class LFlareGroup;

class SYSCORE_API StdSystem {
public:
	bool pending; // 4h
	float fade; // 8h
	/* current unknown members
		void* unk; // Ch
		void* unk; // 10h
		void* unk; // 14h
		void* unk; // 18h
		void* unk; // 1Ch*/
	void* m_debugStreamUnk; // 20h
		/*void* unk; // 24h
		void* unk; // 28h
		void* unk; // 2Ch
		void* unk; // 30h
		void* unk; // 34h
		void* unk; // 38h
		void* unk; // 3Ch
		void* unk; // 40h
	*/
	Matrix4f* matrix;
	char* bloRoot; // 48h
	char* texRoot; // 4Ch	
	char* baseDir; // 50h
	char* fileName;	 // 54h
	AyuHeap heaps[8]; //58h
	int heapNum; // 198h
	/*	void* unk; // 19Ch
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
	*/
	Shape* shape; // 1FCh
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
	//AnimData* findAnimation(char*);
	//AnimData* findAnyAnimation(char*);
	//GfxobjInfo* findAnyGfxObject(char*, unsigned int);
	int			 findAnyIndex(char*, char*);
	//GfxobjInfo* findGfxObject(char*, unsigned int);
	//AnimData* findIndexAnimation(char*, int);
	//GfxobjInfo* findTexture(Texture*);
	void		 flushLFlares(Graphics*);
	void		 genAge(AgeServer*);
	void		 getAppMemory(char*);
	float		 getFade();
	float		 getHalfRand(float);
	//AyuHeap* getHeap(int);
	int			 getHeapNum();
	//LFInfo* getLFlareInfo();
	double		 getRand(float);
	Shape* getShape(char*, char*, char*, bool);
	void		 initLFlares(int);
	void		 invalidateObjs(unsigned int, unsigned int);
	bool		 isActive();
	bool		 isShutdown();
	//AnimData* loadAnimation(Shape*, char*, bool);
	void		 loadBundle(char*, bool);
	//Shape* loadShape(char*, bool);
	//Texture* loadTexture(char*, bool);
	void		 onceInit();
	//LFlareGroup* registerLFlare(Texture*);
	void		 resetHeap(int, int);
	void		 resetLFlares();
	bool		 resetPending();
	void		 set2DRoot(char*, char*);
	void		 setActive(bool);
	void		 setDataRoot(char*);
	void		 setFade(float, float);
	void		 setFrameClamp(int);
	void		 setHeap(int);
	void		 setTextureBase(char*, char*);
	void		 softReset();
	static char* stringDup(char*);
};

#endif