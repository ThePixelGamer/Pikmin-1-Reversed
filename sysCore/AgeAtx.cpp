#include "AgeAtx.h"

#include "System/System.h"

AtxDirectRouter::AtxDirectRouter(char* a2) {
	if (strcmp(a2, "self")) {
		this->m_dword4 = StdSystem::stringDup(a2);
	}
	else {
		this->m_dword4 = gsys->m3B8h;
	}
	this->m_networkStream = 0;
}

void AtxStream::init() {
	this->m_dwordC = 0;
}

bool AtxStream::open(char* unk, int unk2) {
	AtxRouter* router = gsys->getAtxRouter();
	if (!router)
		return false;

	if (router->openRoute(this, unk2)) {
		this->write(unk, 4);

	}
	return true;
}