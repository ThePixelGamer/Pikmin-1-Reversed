#include "RamStream.h"

RamStream::RamStream(void * _buffer, int _length) : RandomAccessStream() {
	this->m_buffer = (char *)_buffer;
	this->m_position = 0;
	this->m_length = _length;
}

void RamStream::read(void * buffer, int amount) {
	memcpy(buffer, &this->m_buffer[this->m_position], amount);
	this->m_position += amount;
}

void RamStream::write(void * src, int amount) {
	memcpy(&this->m_buffer[this->m_position], src, amount);
	this->m_position += amount;
}

int RamStream::getPending() {
	return this->m_length - this->m_position;
}

int RamStream::getPosition() {
	return this->m_position;
}

void RamStream::setPosition(int _position) {
	this->m_position = _position;
}

int RamStream::getLength() {
	return this->m_length;
}

void RamStream::setLength(int _length) {
	this->m_length = _length;
}
