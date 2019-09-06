#include "AtxStream.h"
#include "AtxRouter.h"
#include "../System/System.h"

void ATXPRINT(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	char dest[1024];

	if (sysCon) {
		if ("Atx")
			sysCon->print("%s: ", "Atx");
		vsprintf(dest, fmt, args);
		if (strlen(dest)) {
			sysCon->write(dest, strlen(dest));
		}
	}
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
		int identifier = this->readInt();
		if (identifier == 0xFFFF)
			return false;
		else
		{
			this->flush();
			return true;
		}
	}
	else
	{
		ATXPRINT("Could not open route to server\n");
		gsys->setAtxRouter(NULL);
		return false;
	}
}