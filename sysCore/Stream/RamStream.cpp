#include "RamStream.h"

RamStream::RamStream(const char *_buffer, size_t _length)
    : RandomAccessStream(), m_buffer(_buffer) {
  this->m_position = 0;
  this->m_length = _length;
}

void RamStream::read(void *buffer, int amount) {
  memcpy(buffer, &this->m_buffer[this->m_position], amount);
  this->m_position += amount;
}

void RamStream::write(void *src, int amount) {
  memcpy((void *)&this->m_buffer[this->m_position], src, amount);
  this->m_position += amount;
}

int RamStream::getPending() { return this->m_length - this->m_position; }

int RamStream::getPosition() { return this->m_position; }

void RamStream::setPosition(int _position) { this->m_position = _position; }

int RamStream::getLength() { return this->m_length; }

void RamStream::setLength(int _length) { this->m_length = _length; }
