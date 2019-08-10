#include "SRT.h"

SRT::SRT() {}

SRT::SRT(const SRT& a2) {
	this->mUnk1 = a2.mUnk1;
	this->mUnk2 = a2.mUnk2;
	this->mUnk3 = a2.mUnk3;
}

void SRT::read(RandomAccessStream& a2) {
	this->mUnk1.read(a2);
	this->mUnk2.read(a2);
	this->mUnk3.read(a2);
}

void SRT::write(RandomAccessStream& a2) {
	this->mUnk1.write(a2);
	this->mUnk2.write(a2);
	this->mUnk3.write(a2);
}