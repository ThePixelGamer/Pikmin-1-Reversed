#include <Atx/AtxRouter.h>
#include <Atx/AtxStream.h>
#include <Networking/TcpStream.h>
#include <System/System.h>

void ATXPRINT(const char* fmt, ...)
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

void AtxStream::init() { m_0C = 0; }

bool AtxStream::open(char* name, int port)
{
    AtxRouter* router = gsys->getAtxRouter();
    if (!router)
        return false;

    if (!router->openRoute(this, port))
    {
        ATXPRINT("Could not open route to server\n");
        gsys->setAtxRouter(NULL);
        return false;
    }

    write(name, 4);
    if (m_stream->readInt() == 0xFFFF)
    {
        return false;
    }

    flush();
    return true;
}

void AtxStream::close() { gsys->getAtxRouter()->closeRoute(this); }

void AtxStream::flush()
{
    AtxRouter* router = gsys->getAtxRouter();
    router->lock();

    m_stream->flush();

    router->unlock();
}

int AtxStream::getPending()
{
    AtxRouter* router = gsys->getAtxRouter();
    router->lock();

    const int pending = m_stream->getPending();

    router->unlock();
    return pending;
}

void AtxStream::read(void* buffer, int count)
{
    AtxRouter* router = gsys->getAtxRouter();
    router->lock();

    m_stream->read(buffer, count);

    router->unlock();
}

void AtxStream::write(void* buffer, int count)
{
    AtxRouter* router = gsys->getAtxRouter();
    router->lock();

    m_stream->write(buffer, count);

    router->unlock();
}
