#include "FileIO.h"

FileIO::FileIO(const char* _buffer, size_t _length) : RandomAccessStream(), m_buffer(_buffer) {
	this->m_position = 0;
	this->m_length = _length;
}

void FileIO::read(void* buffer, int amount) {
	memcpy(buffer, &this->m_buffer[this->m_position], amount);
	this->m_position += amount;
}

void FileIO::write(void* src, int amount) {
	memcpy((void*)& this->m_buffer[this->m_position], src, amount);
	this->m_position += amount;
}

int FileIO::getPending() {
	return this->m_length - this->m_position;
}

int FileIO::getPosition() {
	return this->m_position;
}

void FileIO::setPosition(int _position) {
	this->m_position = _position;
}

int FileIO::getLength() {
	return this->m_length;
}

void FileIO::setLength(int _length) {
	this->m_length = _length;
}
