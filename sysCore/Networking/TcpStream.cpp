#include "TcpStream.h"

TcpStream::TcpStream() {
  this->m_wSock = 0;
  this->m_streamInUse = 0;
}

TcpStream::TcpStream(WSocket *sock) {
  this->m_wSock = new WSocket;
  this->m_wSock->m_listeningSock = sock->m_listeningSock;
  this->m_wSock->connect();
}

void TcpStream::read(void *buf, int len) {
  const int oldStreamType = gsys->setStreamType(this->m_streamInUse);
  this->m_wSock->read((char *)buf, len);
  gsys->setStreamType(oldStreamType);
}

void TcpStream::write(void *buf, int len) {
  this->m_wSock->write((char *)buf, len);
}

int TcpStream::getPending() { return this->m_wSock->pending(); }

int TcpStream::getAvailable() { return 0; }

void TcpStream::close() { this->m_wSock->close(); }

void TcpStream::flush() {
  // Oddly enough, this WSocket function doesn't ever get overloaded
  this->m_wSock->flushWrite();
}

bool TcpStream::closing() { return this->m_wSock->closing() != 0; }

bool TcpStream::connect(char *name, int port) {
  this->m_wSock = new WSocket;
  return this->m_wSock->open(name, port) != 0;
}
