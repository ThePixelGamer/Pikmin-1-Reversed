#include <Graphics/Graphics.h>
#include <Object/AnimobjInfo.h>
#include <Stream/CmdStream.h>
#include <System/StdSystem.h>
#include <System/System.h>
#include <Texture/Texture.h>

//////////////////////////////////////////////////////////////////////
// StdSystem class functions
//////////////////////////////////////////////////////////////////////

StdSystem::StdSystem() { this->dword10 = 1.0; }

void StdSystem::initSoftReset()
{
    CmdStream::statbuff = 0;
    this->shape = 0;
}

RandomAccessStream* StdSystem::openFile(char*, bool, bool) { return nullptr; }

void StdSystem::copyRamToCache(unsigned int, unsigned int, unsigned int) {}

void StdSystem::copyCacheToRam(unsigned int, unsigned int, unsigned int) {}

void StdSystem::copyWaitUntilDone() {}

void StdSystem::copyCacheToTexture(CacheTexture*) {}

void StdSystem::Activate(bool) {}

void StdSystem::parseArchiveDirectory(char*, char*) {}

void StdSystem::startLoading(LoadIdler*, bool, unsigned int) {}

void StdSystem::endLoading() {}

void StdSystem::Shutdown() { this->unkShutdownCode = 0x80000000; }

void StdSystem::addAnimation(AnimData* anim, char* dup)
{
    AnmobjInfo* gfxobj = new AnmobjInfo();
    gfxobj->str = StdSystem::stringDup(dup);
    gfxobj->id32.setID('_anm');
    gfxobj->animData = anim;
    this->addGfxObject(gfxobj);
}

void StdSystem::addGfxObject(GfxobjInfo* a2)
{
    this->gfx.insertAfter(a2);
    this->m_toAttachObjs = 1;
}

void StdSystem::addTexture(Texture* toAdd, char* name)
{
    TexobjInfo* tex = new TexobjInfo();
    tex->str = StdSystem::stringDup(name);
    tex->id32.setID('_tex');
    tex->texData = toAdd;
    toAdd->m_objInfo = tex;
    this->addGfxObject(tex);
}
void StdSystem::ageAnyAnimations() {}

void StdSystem::attachObjs()
{
    if (this->m_toAttachObjs)
    {
        for (GfxobjInfo* i = this->gfx.next; i != &this->gfx; i = i->next)
        {
            if (i->attached == false)
            {
                i->attach();
                i->attached = 1;
            }
        }
        this->m_toAttachObjs = false;
    }
}

void StdSystem::detachObjs() {}

// AnimData* StdSystem::findAnimation(char*) {}
// AnimData* StdSystem::findAnyAnimation(char*) {}
// GfxobjInfo* StdSystem::findAnyGfxObject(char*, unsigned int) {}
int StdSystem::findAnyIndex(char*, char*) { return 0; }
GfxobjInfo* StdSystem::findGfxObject(char* str, unsigned __int32 id)
{
    for (GfxobjInfo* i = this->gfx.next; i != &this->gfx; i = i->next)
    {
        if (i->id32 == id && !strcmp(i->str, str))
            return i;
    }
    return nullptr;
}
// AnimData* StdSystem::findIndexAnimation(char*, int) {}
TexobjInfo* StdSystem::findTexture(Texture* toFind)
{
    for (TexobjInfo* i = static_cast<TexobjInfo*>(this->gfx.next); i != &this->gfx;
         i = static_cast<TexobjInfo*>(i->next))
    {
        if (i->texData == toFind)
            return i;
    }
    return nullptr;
}
void StdSystem::flushLFlares(Graphics*) {}
void StdSystem::genAge(AgeServer& server)
{
    server.StartSection("StdSystem", true);
    server.EndSection();
}
void StdSystem::getAppMemory(char* dest)
{
    // TODO
    int free = this->getHeap(2)->getFree();
    float fwee = free / 1024.0;
    sprintf(dest, "FreeMem %.2fk", fwee, (static_cast<int>(fwee) >> 32));
}
AyuHeap* StdSystem::getHeap(int heapIndex) { return &this->heaps[heapIndex]; }

int StdSystem::getHeapNum() { return this->heapNum; }

// LFInfo* StdSystem::getLFlareInfo() {}

Shape* StdSystem::getShape(char* file, char* a3, char* a4, bool hasCwd)
{ // TODO
    RandomAccessStream* stream = this->openFile(file, hasCwd, true);
    BaseShape* ret;
    if (stream)
    {
        // ret = new Shape();
        // this->shape = ret;
        // TODO
    }
    return nullptr;
}

void StdSystem::initLFlares(int) {}

void StdSystem::invalidateObjs(unsigned __int32 unk, unsigned __int32 unk2)
{
    GfxobjInfo* next;
    for (GfxobjInfo* i = this->gfx.next; i != &this->gfx; i = next)
    {
        next = i->next;
        if ((int)i >= unk && (int)i < unk2)
            i->remove();
    }
}

bool StdSystem::isActive() { return (this->unkShutdownCode & 0x200000) == 0x200000; }

bool StdSystem::isShutdown() { return (this->unkShutdownCode) == 0x80000000; }

// AnimData* StdSystem::loadAnimation(Shape*, char*, bool) {}

void StdSystem::loadBundle(char*, bool) {}

// Shape* StdSystem::loadShape(char*, bool) {}

Texture* StdSystem::loadTexture(char* name, bool hasCwd)
{
    TexobjInfo* objInfo = static_cast<TexobjInfo*>(this->findGfxObject(name, '_tex'));
    if (objInfo)
        return objInfo->texData;
    Texture* tex = nullptr;
    RandomAccessStream* stream = this->openFile(name, hasCwd, true);
    if (stream)
    {
        tex = new Texture();
        tex->read(*stream);
        stream->close();
    }
    return tex;
}

void StdSystem::onceInit()
{
    this->matrixUnk = 0x1000;
    this->matrix = new (0x20) Matrix4f[this->matrixUnk]();
}
// LFlareGroup* StdSystem::registerLFlare(Texture*) {}
void StdSystem::resetHeap(int heapIndex, int resetTo) { this->heaps[heapIndex].reset(resetTo); }
void StdSystem::resetLFlares() { this->m_lFlares = nullptr; }
void StdSystem::setActive(bool toSet)
{
    // TODO
    bool active = (toSet != false); // ? this->unkShutdownCode |= 0x200000 : this->unkShutdownCode &= -0x200001;

    this->Activate(active);
}
void StdSystem::setDataRoot(char* dataRoot) {}
void StdSystem::setFade(float, float) {}
void StdSystem::setFrameClamp(int newc) { this->m_frameClamp = newc; }
int StdSystem::setHeap(int heap)
{
    int retVal = heapNum;
    heapNum = heap;
    return retVal;
}
void StdSystem::setTextureBase(char*, char*) {}
void StdSystem::softReset() { this->pending = 1; }

char* StdSystem::stringDup(char* str)
{
    size_t size = strlen(str) + 1;
    char* dst = new char[size];
    memcpy(dst, str, size);
    return dst;
}

float StdSystem::getHalfRand(float a) { return (rand() / 32767.0 - 0.5) * a; }

double StdSystem::getRand(float a) { return rand() / 32767.0 * a; }

bool StdSystem::resetPending() { return this->pending; }

void StdSystem::set2DRoot(char* _bloroot, char* _texroot)
{
    this->bloRoot = _bloroot;
    this->texRoot = _texroot;
}
