#include "SRT.h"

SRT::SRT() {}

void SRT::read(RandomAccessStream& a2) {
	this->m_scale.read(a2);
	this->m_rotation.read(a2);
	this->m_position.read(a2);
}

void SRT::write(RandomAccessStream& a2) {
	this->m_scale.write(a2);
	this->m_rotation.write(a2);
	this->m_position.write(a2);
}