// WSocket.cpp: implementation of the WSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "WSocket.h"

bool WSocket::checkForConnections() {
	fd_set readfds;
	readfds.fd_count = 0;
	readfds.fd_array[readfds.fd_count++] = this->m_listeningSock;

	const struct timeval* timeout;
	memset((void*)timeout, 0, sizeof(struct timeval));
	unsigned int unused = 1;

	int selectVal = select(unused, &readfds, 0, 0, timeout);
	if (selectVal < 0)
		return false;
	if (selectVal > 0 && __WSAFDIsSet(this->m_listeningSock, &readfds))
		return true;

	return false;
}