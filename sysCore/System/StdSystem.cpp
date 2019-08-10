#include "StdSystem.h"

//////////////////////////////////////////////////////////////////////
// FileRandomAccessStream class functions
//////////////////////////////////////////////////////////////////////

FileRandomAccessStream::FileRandomAccessStream(FILE* fpointer, char* cwd) : RandomAccessStream() {
	this->fStream = fpointer;
	this->currentWorkingDir = cwd;
	this->dwordC = 0;

	int offset = this->getPosition();
	fseek(this->fStream, 0, SEEK_END);
	this->fileSize = ftell(this->fStream);
	fseek(this->fStream, offset, SEEK_SET);
}

int FileRandomAccessStream::getPosition() {
	return ftell(this->fStream);
}

//////////////////////////////////////////////////////////////////////
// StdSystem class functions
//////////////////////////////////////////////////////////////////////

StdSystem::StdSystem()
{

}

void StdSystem::initSoftReset() {

}

RandomAccessStream* StdSystem::openFile(char*, bool, bool) {
	return new FileRandomAccessStream(0, 0);
}

void StdSystem::copyRamToCache(unsigned int, unsigned int, unsigned int) {

}

void StdSystem::copyCacheToRam(unsigned int, unsigned int, unsigned int) {

}

void StdSystem::copyWaitUntilDone() {

}

void StdSystem::copyCacheToTexture(CacheTexture*) {

}

void StdSystem::Activate(bool) {

}

void StdSystem::parseArchiveDirectory(char*, char*) {

}

void StdSystem::startLoading(LoadIdler*, bool, unsigned int) {

}

void StdSystem::endLoading() {

}


void StdSystem::addAnimation(AnimData*, char*) {}
void StdSystem::addGfxObject(GfxobjInfo* a2) {
	this->gfx.insertAfter(a2);
	this->unkBool = true; //or 1
}

void StdSystem::addTexture(Texture*, char*) {}
void StdSystem::ageAnyAnimations() {}
void StdSystem::attachObjs() {}
void StdSystem::detachObjs() {}
AnimData* StdSystem::findAnimation(char*) {}
AnimData* StdSystem::findAnyAnimation(char*) {}
GfxobjInfo* StdSystem::findAnyGfxObject(char*, unsigned int) {}
int StdSystem::findAnyIndex(char*, char*) {}
GfxobjInfo* StdSystem::findGfxObject(char*, unsigned int) {}
AnimData* StdSystem::findIndexAnimation(char*, int) {}
GfxobjInfo* StdSystem::findTexture(Texture*) {}
void StdSystem::flushLFlares(Graphics*) {}
void StdSystem::genAge(AgeServer*) {}
void StdSystem::getAppMemory(char*) {}
float StdSystem::getHalfRand(float) {}
AyuHeap* StdSystem::getHeap(int) {}
int StdSystem::getHeapNum() {}
LFInfo* StdSystem::getLFlareInfo() {}
Shape* StdSystem::getShape(char*, char*, char*, bool) {}
void StdSystem::initLFlares(int) {}
void StdSystem::invalidateObjs(unsigned int, unsigned int) {}
bool StdSystem::isActive() { 
	return (this->unkShutdownCode & 0x200000) == 0x200000; 

}
bool StdSystem::isShutdown() {
	return (this->unkShutdownCode) == 0x80000000;
}

AnimData* StdSystem::loadAnimation(Shape*, char*, bool) {}
void StdSystem::loadBundle(char*, bool) {}
Shape* StdSystem::loadShape(char*, bool) {}
Texture* StdSystem::loadTexture(char*, bool) {}
void StdSystem::onceInit() {}
void StdSystem::parseArchiveDirectory(char*, char*) {}
LFlareGroup* StdSystem::registerLFlare(Texture*) {}
void StdSystem::resetHeap(int, int) {}
void StdSystem::resetLFlares() {}
void StdSystem::resetPending() {}
void StdSystem::set2DRoot(char*, char*) {}
void StdSystem::setActive(bool) {}
void StdSystem::setDataRoot(char*) {}
void StdSystem::setFade(float, float) {}
void StdSystem::setFrameClamp(int) {}
void StdSystem::setHeap(int) {}
void StdSystem::setTextureBase(char*, char*) {}
void StdSystem::softReset() {}

char* StdSystem::stringDup(char* str) {
	size_t size = strlen(str) + 1;
	char* dst = new char[size];
	memcpy(dst, str, size);
	return dst;
}

double StdSystem::getHalfRand(float a) {
	return (rand() / 32767.0 - 0.5) * a;
}

double StdSystem::getRand(float a) {
	return rand() / 32767.0 * a;
}

bool StdSystem::resetPending() {
	return this->pending;
}

void StdSystem::set2DRoot(char* _bloroot, char* _texroot) {
	this->bloRoot = _bloroot;
	this->texRoot = _texroot;
}
