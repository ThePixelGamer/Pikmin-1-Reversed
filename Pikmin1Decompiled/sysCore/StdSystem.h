#ifndef STDSYSTEM_H
#define STDSYSTEM_H

#include <cstdarg>
#include <algorithm>

class CacheTexture;
class LoadIdler;
class AnimData;
class GfxobjInfo;
class Texture;
class Graphics;
class AgeServer;
class AyuHeap;
class LFInfo;
class Shape;
class LFlareGroup;

class SYSCORE_API StdSystem {
public:
	StdSystem();
	StdSystem(const StdSystem&);
	~StdSystem();

	virtual void initSoftReset();
	virtual void openFile(char*, bool, bool);
	virtual void copyRamToCache(unsigned int, unsigned int, unsigned int);
	virtual void copyCacheToRam(unsigned int, unsigned int, unsigned int);
	virtual void copyWaitUntilDone();
	virtual void copyCacheToTexture(CacheTexture*);
	virtual void Activate(bool);
	virtual void parseArchiveDirectory(char*, char*);
	virtual void sndPlaySe(unsigned int) = 0;
	virtual void startLoading(LoadIdler*, bool, unsigned int);
	virtual void endLoading();
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
	char*		 stringDup(char*);

	StdSystem operator=(const StdSystem&);*/
};

#endif

