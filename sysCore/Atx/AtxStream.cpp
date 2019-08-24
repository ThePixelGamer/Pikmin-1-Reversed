#include "AtxStream.h"
#include "AtxRouter.h"
#include "../System/System.h"

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