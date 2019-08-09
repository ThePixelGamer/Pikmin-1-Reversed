#include "AgeAtx.h"

#include "System/System.h"

AtxDirectRouter::AtxDirectRouter(char* a2) {
    if(strcmp(a2, "self")) {
        this->m_dword4 = StdSystem::stringDup(a2);
    }
    else {
        this->m_dword4 = gsys->m3B8h;
    }
    this->m_networkStream = 0;
}