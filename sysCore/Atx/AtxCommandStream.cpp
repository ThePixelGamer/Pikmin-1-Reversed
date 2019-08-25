#include "../System/System.h"
#include "AtxCommandStream.h"
#include "../Networking/TcpStream.h"
void ATXCOMMANDSTREAMPRINT(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	char dest[1024];

	if(sysCon) {
		if ("Atx")
			sysCon->print("%s: ", "Atx");
		vsprintf(dest, fmt, args);
		if(strlen(dest)) {
			sysCon->write(dest, strlen(dest));
		}
	}
}

bool AtxCommandStream::checkCommands() {
	if (this->m_stream->getPending())
		return false;
	
	int command = this->m_stream->readInt();
	if (command == 1) {
		ATXCOMMANDSTREAMPRINT("Atx - Sending identification information\n");
		this->writeString(this->filePath);
	}
	else {
		if (command == 0xFFFF) {
			ATXCOMMANDSTREAMPRINT("Atx - Server is closing\n");
			this->m_baseApp->stopAgeServer();
			return false;
		}
		if (command == 'age\0')
			this->m_baseApp->startAgeServer();
	}
	return true;
}