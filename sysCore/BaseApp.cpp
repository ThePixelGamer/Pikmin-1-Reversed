#include "BaseApp.h"
#include "Networking/TcpStream.h"

#include "System/System.h"
void BASEAPPPRINT(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	char dest[1024];

	if(sysCon) {
		if ("baseApp")
			sysCon->print("%s: ", "baseApp");
		vsprintf(dest, fmt, args);
		if(strlen(dest)) {
			sysCon->write(dest, strlen(dest));
		}
	}
}

BaseApp::BaseApp() : Node("<Node>") {
	this->m_unkInt = 0;
	this->m_cmdStream = 0;
	this->m_server = 0;
	this->m_unkByte = true;
	nodeMgr->firstNode()->add(this);
}

void BaseApp::genAge(AgeServer& serv) {
	gsys->genAge(serv);
}

void BaseApp::startAgeServer() {
	if (!this->m_server) {
		BASEAPPPRINT("Atx - Wants to open Age service\n");
		AgeServer* newServer = new AgeServer;

		bool hasOpened = newServer->Open();
		if (hasOpened)
		{
			this->m_server = newServer;
			this->m_server->NewNodeWindow(this->Name());
			this->genAgeNode(*this->m_server);
			this->m_server->Done();
		}
	}
}

void BaseApp::stopAgeServer() {
	if (this->m_server) {
		this->m_server->m_stream->writeInt(0xFFFF);
		this->m_server->m_stream->flush();
		this->m_server = 0;
	}
}