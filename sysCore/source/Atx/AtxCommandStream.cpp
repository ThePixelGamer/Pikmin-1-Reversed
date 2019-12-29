#include <Atx/AtxCommandStream.h>
#include <Networking/TcpStream.h>
#include <System/System.h>

enum Command
{
	Closing = 0xFFFF,
	GetIdentification = 1,
	InitAgeserver = 'age\0',
};

void ATXCOMMANDSTREAMPRINT(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char dest[1024];

    if (sysCon)
    {
        if ("Atx")
            sysCon->print("%s: ", "Atx");
        vsprintf(dest, fmt, args);
        if (strlen(dest))
        {
            sysCon->write(dest, strlen(dest));
        }
    }
}

bool AtxCommandStream::checkCommands()
{
    if (this->m_stream->getPending())
        return false;

    const int command = this->m_stream->readInt();
    switch (static_cast<Command>(command))
    {
	case Closing:
        ATXCOMMANDSTREAMPRINT("Atx - Server is closing\n");
        this->m_baseApp->stopAgeServer();
        return false;
	case GetIdentification:
        ATXCOMMANDSTREAMPRINT("Atx - Sending identification information\n");
        this->writeString(this->filePath);
        break;
	case InitAgeserver:
        this->m_baseApp->startAgeServer();
        break;
    }
    return true;
}
