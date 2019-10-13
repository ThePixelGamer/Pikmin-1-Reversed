#include <App/BaseApp.h>
#include <Networking/TcpStream.h>
#include <System/System.h>

void BASEAPPPRINT(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char dest[1024];

    if (sysCon)
    {
        if ("baseApp")
            sysCon->print("%s: ", "baseApp");
        vsprintf(dest, fmt, args);
        if (strlen(dest))
        {
            sysCon->write(dest, strlen(dest));
        }
    }
}

BaseApp::BaseApp() : Node("<Node>")
{
    this->m_unkInt = 0;
    this->m_cmdStream = 0;
    this->m_server = 0;
    this->m_unkByte = true;
    nodeMgr->firstNode()->add(this);
}

BaseApp::~BaseApp()
{
    BASEAPPPRINT("default baseApp deconstructor\n");
    if (this->m_cmdStream)
    {
        this->m_cmdStream->m_stream->writeInt(0xFFFF);
        this->m_cmdStream->m_stream->flush();
    }
    this->stopAgeServer();
    nodeMgr->Del(this);
}

void BaseApp::genAge(AgeServer& serv) { gsys->genAge(serv); }

void BaseApp::softReset()
{
    this->stopAgeServer();
    this->child = nullptr;
    this->m_node1.init("[Windows]");
    gsys->initSoftReset();
}

void BaseApp::useHeap(int heap) { gsys->setHeap(heap); }

bool BaseApp::idleUpdate()
{
    bool returnValue = false;
    if (this->m_cmdStream)
    {
        const int updateCode = this->m_cmdStream->checkCommands();
        if (updateCode == -1)
        {
            this->m_cmdStream = nullptr;
        }
        else if (updateCode)
        {
            returnValue = true;
        }
    }
    if (this->m_server)
    {
        const int updateCode = this->m_server->update();
        if (updateCode == -1)
        {
            this->stopAgeServer();
            this->m_server = nullptr;
        }
        else if (updateCode)
        {
            returnValue = true;
        }
    }
    return returnValue;
}

void BaseApp::startAgeServer()
{
    if (!this->m_server)
    {
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

void BaseApp::stopAgeServer()
{
    if (this->m_server)
    {
        BASEAPPPRINT("Atx - Wants to close Age service\n");
        this->m_server->m_stream->writeInt(0xFFFF);
        this->m_server->m_stream->flush();
        this->m_server = 0;
    }
}

double BaseApp::rnd() { return rand() / 32767.0; }

double BaseApp::rnd(float mult) { return this->rnd() * mult; }
