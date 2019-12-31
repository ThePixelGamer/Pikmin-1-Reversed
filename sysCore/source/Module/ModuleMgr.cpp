#include <Module/ModuleMgr.h>

SYSCORE_API ModuleMgr* modMgr;

ModuleMgr::ModuleMgr()
{
    MODULEPRINT("Creating moduleMgr ...\n");

    this->topModule = new Module();
    this->topModule->next = this->topModule;
    this->topModule->prev = this->topModule->next;

    this->moduleCount = 0;
}

ModuleMgr::~ModuleMgr()
{
	// Unload every module
    Module* nxt;
    for (Module* i = this->topModule->prev; i != this->topModule;)
    {
        nxt = i->prev;
        this->UnLoad(i);
        i = nxt;
    }
}

void* ModuleMgr::Alloc(char* name)
{
    void* object;
    for (Module* i = this->topModule->prev; i != topModule; i = i->prev)
    {
        object = (i->m_newObjAddr)(name);
        if (object)
        {
            return object;
        }
    }
    MODULEPRINT("ModuleMgr: !!!!! could not allocate %s !!!!!\n", name);
    return 0;
}

void ModuleMgr::UnLoad(Module* toDel)
{
    toDel->prev->next = toDel->next;
    toDel->next->prev = toDel->prev;

    this->moduleCount--;

    delete toDel;
}

Module* ModuleMgr::findModule(char* name)
{
    for (Module* i = this->topModule->prev; i != this->topModule; i = i->prev)
    {
        if (!strcmp(i->libName, name))
            return i;
    }
    return 0;
}

// ebp offset for 'i' is incorrect, should be 8 but is C
void ModuleMgr::listModules()
{
    if (this->topModule->prev != this->topModule)
    {
        char* unk = (this->moduleCount != 1) ? "es" : "e";

        for (Module * i = this->topModule->prev; i != this->topModule; i = i->prev)
        {
        }
    }
}

Module* ModuleMgr::loadModule(char* name)
{
    Module* newModule = this->findModule(name);

    if (!newModule)
    {
        newModule = new Module();
        newModule->Load(name);
        newModule->prev = this->topModule;
        newModule->next = this->topModule->next;

        this->topModule->next = newModule;

        newModule->next->prev = newModule;
        this->moduleCount++;

        if (newModule->m_autoStartAddr)
            (newModule->m_autoStartAddr)();
    }

    return newModule;
}
