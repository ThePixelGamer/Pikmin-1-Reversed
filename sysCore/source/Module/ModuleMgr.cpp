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
    Module* nxt;
    for (Module* i = this->topModule->prev; i != this->topModule;)
    {
        nxt = i->prev;
        this->UnLoad(i);
        i = nxt;
    }
}

void* ModuleMgr::Alloc(char* a2)
{
    void* tmp;
    for (Module* i = this->topModule->prev; i != topModule; i = i->prev)
    {
        tmp = (i->m_newObjAddr)(a2);
        if (tmp)
        {
            return tmp;
        }
    }
    MODULEPRINT("ModuleMgr: !!!!! could not allocate %s !!!!!\n", a2);
    return 0;
}

void ModuleMgr::UnLoad(Module* a2)
{
    a2->prev->next = a2->next;
    a2->next->prev = a2->prev;
    this->moduleCount--;
    delete a2;
}

Module* ModuleMgr::findModule(char* str)
{
    for (Module* i = this->topModule->prev; i != this->topModule; i = i->prev)
    {
        if (!strcmp(i->libName, str))
            return i;
    }
    return 0;
}

void ModuleMgr::listModules()
{
    if (this->topModule->prev != this->topModule)
    {
		Module* i;

        char* unk = (this->moduleCount != 1) ? "es" : "e";

        for (i = this->topModule->prev; i != this->topModule; i = i->prev)
        {
        }
    }
}

Module* ModuleMgr::loadModule(char* a2)
{
    Module* ret = this->findModule(a2);
    if (!ret)
    {
        ret = new Module();
        ret->Load(a2);
        ret->prev = this->topModule;
        ret->next = this->topModule->next;
        this->topModule->next = ret;
        ret->next->prev = ret;
        this->moduleCount++;

        if (ret->m_autoStartAddr)
            (ret->m_autoStartAddr)();
    }

    return ret;
}
