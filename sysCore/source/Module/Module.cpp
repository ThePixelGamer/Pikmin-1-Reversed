#include <Module/Module.h>

void MODULEPRINT(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char dest[1024];

    if (sysCon)
    {
        if ("ModuleMgr")
            sysCon->print("%s: ", "ModuleMgr");
        vsprintf(dest, fmt, args);
        if (strlen(dest))
        {
            sysCon->write(dest, strlen(dest));
        }
    }
}

Module::~Module()
{
    if (this->pHInstance)
    {
        this->m_newObjAddr = 0;
        this->m_autoStartAddr = 0;
        FreeLibrary(this->pHInstance);
        this->pHInstance = 0;
        free(this->libName);
    }
}

void Module::Load(char* source)
{
    this->libName = strdup(source);
    MODULEPRINT("opening %s\n", this->libName);

    this->pHInstance = LoadLibraryA(this->libName);
    if (this->pHInstance)
    {
        this->m_newObjAddr = (DLLFuncChar)GetProcAddress(this->pHInstance, "NewObject");      //(char)
        this->m_objListAddr = (DLLFuncVoid)GetProcAddress(this->pHInstance, "GetObjectList"); //(void)
        this->m_autoStartAddr = (DLLFuncVoid)GetProcAddress(this->pHInstance, "AutoStart");   //(void)
    }
    else
    {
        this->m_newObjAddr = 0;
        this->m_objListAddr = 0;
        this->m_autoStartAddr = 0;
    }
}

static int itemCount;

void Module::menuPlugins(MenuPlugin* menu, HMENU hmenu)
{
    for (Object* i = (this->m_objListAddr)(); i->str; i++)
    {
        if (i->load)
        {
            UINT message = RegisterWindowMessageA(i->str);
            MenuPlugin* unk = new MenuPlugin();
            unk->prev = message;
            unk->name = i->str;
            menu->setNext(unk);

            MENUITEMINFO mi;
            mi.cbSize = sizeof(MENUITEMINFO);
            mi.fMask = MIIM_TYPE | MIIM_ID;
            mi.wID = message;
            mi.fType = MFT_STRING;
            mi.dwTypeData = i->str;
            mi.cch = strlen(i->str);
            InsertMenuItemA(hmenu, itemCount++, 1, &mi);
        }
    }
}