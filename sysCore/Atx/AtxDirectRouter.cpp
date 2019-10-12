#include "AtxDirectRouter.h"

// cannot include both in header because of error LNK2001 aka circling
// dependency
#include "../Networking/TcpStream.h"
#include "../System/System.h"

AtxDirectRouter::AtxDirectRouter(char *_name) {
  this->m_hostname =
      strcmp(_name, "self") ? StdSystem::stringDup(_name) : gsys->m_hostName;
  this->m_networkStream = 0;
}

bool AtxDirectRouter::openRoute(AtxStream *stream, int port) {
  this->m_networkStream = new TcpStream();
  this->m_networkStream->m_streamInUse = NETWORK_STREAM; // defined in Stream.h

  // if it can't connect to the host at port 1369, the route wasn't opened,
  // close!
  if (!this->m_networkStream->connect(this->m_hostname, 1369))
    return false;

  // if the current window has been created, we set the socket to asynchronous
  if (sysCurrWnd)
    this->m_networkStream->m_wSock->setASync(sysCurrWnd, 0x443,
                                             WM_MOUSEACTIVATE, -1);

  stream->m_stream = this->m_networkStream;
  return true;
}

void AtxDirectRouter::setWindow(unsigned __int32 hwnd) {
  if (hwnd)
    if (this->m_networkStream)
      this->m_networkStream->m_wSock->setASync((HWND)hwnd, 0x433, 0x21,
                                               SOCKET_ERROR);
}