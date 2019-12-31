#include <Networking/WSocket.h>

void WSOCKETPRINT(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char dest[1024];

    if (sysCon)
    {
        if ("wSocket")
            sysCon->print("%s: ", "wSocket");
        vsprintf(dest, fmt, args);
        if (strlen(dest))
        {
            sysCon->write(dest, strlen(dest));
        }
    }
}

void WSOCKETHALT(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char dest[1024];
    vsprintf(dest, fmt, args);
    System::halt("c:\\development\\dolphinpiki\\syscore\\wsocket.cpp", 7, dest);
}

bool WSocket::checkForConnections()
{
    fd_set readfds;
    // see: https://linux.die.net/man/3/fd_set for explanation
    FD_ZERO(&readfds);
    FD_SET(0, &readfds);

    struct timeval timeout;
    ZeroMemory(&timeout, sizeof(timeval));

    int unused = 1;
    int fDescriptorCount = select(1, &readfds, 0, 0, &timeout);
    if (fDescriptorCount < 0)
        return false;
    if (fDescriptorCount > 0 && __WSAFDIsSet(this->m_listeningSock, &readfds))
        return true;

    return false;
}

void WSocket::close() { closesocket(this->m_acceptedSock); }

bool WSocket::closing() { return false; }

void WSocket::connect()
{
    struct sockaddr addr;
    int addrlen = 16;
    this->m_acceptedSock = accept(this->m_listeningSock, &addr, &addrlen);

    WSOCKETPRINT("got connected socket = %d : connection from %d.%d.%d.%d\n", this->m_acceptedSock, addr.sa_data[2],
                 addr.sa_data[3], addr.sa_data[4], addr.sa_data[5]);
}

bool WSocket::create(char* unused, int port)
{
    this->m_listeningSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (this->m_listeningSock <= 0)
    {
        WSOCKETPRINT("Could not create socket!!\n");
        return false;
    }
    WSOCKETPRINT("got socket id %d\n", this->m_listeningSock);

    struct sockaddr_in name;
    name.sin_family = AF_INET;             // AF_INET = 2
    name.sin_addr.S_un.S_addr = AF_UNSPEC; // AF_UNSPEC = 0
    name.sin_port = htons(port);
    if (bind(this->m_listeningSock, reinterpret_cast<SOCKADDR*>(&name), 16))
    {
        WSOCKETPRINT("Error binding socket!!\n");
        return false;
    }
    else
    {
        listen(this->m_listeningSock, 0x8000);
        return true;
    }
}

void WSocket::flushWrite() {} // empty function

void WSocket::init()
{
    WORD wVersionRequested = 2;
    WSAData data;

    if (WSAStartup(wVersionRequested, &data))
        WSOCKETPRINT("Can't open win sock DLL !!\n");
}

bool WSocket::open(char* name, int port)
{
    hostent* host = gethostbyname(name);
    if (host)
    {
        this->m_acceptedSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (this->m_acceptedSock <= 0)
        {
            WSOCKETPRINT("Could not create socket!!\n");
            return false;
        }

        sockaddr_in name;
        memset(&name, 0, sizeof(struct sockaddr_in));
        name.sin_family = AF_INET;             // AF_INET = 2
        name.sin_addr.S_un.S_addr = AF_UNSPEC; // AF_UNSPEC = 0
        name.sin_port = htons(0);

        if (bind(this->m_acceptedSock, (SOCKADDR*)&name, 16))
        {
            WSOCKETPRINT("Error binding socket!!\n");
            return false;
        }
        else
        {
            name.sin_port = htons(port);
            memcpy(&name.sin_addr, *host->h_addr_list, host->h_length);
            if (::connect(this->m_acceptedSock, (SOCKADDR*)&name, 16) == -1)
            {
                WSOCKETPRINT("Could not connect to server\n");
                return false;
            }
            return true;
        }
    }
    else
    {
        WSOCKETPRINT("could not get host by name\n");
        return false;
    }
}

unsigned long WSocket::pending()
{
    unsigned long argp = 0;
    if (ioctlsocket(this->m_acceptedSock, FIONREAD, &argp) < 0)
        return 0;
    else
        return argp;
}

void WSocket::read(void* buf, int len)
{
    while (len)
    {
        int recieved = recv(this->m_acceptedSock, static_cast<char*>(buf), len, 0);
        if (recieved < 0)
        {
            int lastError = WSAGetLastError();
            if (lastError != WSAEWOULDBLOCK)
                WSOCKETHALT("recv on sock %d : error %d", this->m_acceptedSock, lastError);
            WaitMessage();
            recieved = 0;
        }
        len -= recieved;
        buf = static_cast<char*>(buf) + recieved;
    }
}

void WSocket::setASync(HWND hWnd, unsigned __int32 wMsg, unsigned __int32 lEvent, int sock)
{
    int socketToUse = (sock == SOCKET_ERROR) ? this->m_acceptedSock : sock;
    if (WSAAsyncSelect(socketToUse, hWnd, wMsg, lEvent) == -1)
        WSOCKETPRINT("Error switching to Async mode\n");
}

void WSocket::write(void* buf, int len)
{
    signed int writeLimit = 200; // unsure of name
    while (len)
    {
        int sentData = send(this->m_acceptedSock, static_cast<char*>(buf), len, 0);
        if (sentData < 0)
        {
            int lastError = WSAGetLastError();
            if (lastError != WSAEWOULDBLOCK)
                WSOCKETHALT("send error %d", lastError);
            if ((writeLimit--) <= 0)
                WSOCKETHALT("write timeout");
            gsys->sleep(0.01f);
            sentData = 0;
        }
        else
        {
            if (sentData != len)
                WSOCKETPRINT("!!! Not sent all data !!\n");
        }
        len -= sentData;
        buf = static_cast<char*>(buf) + sentData;
    }
}
