#include "RandomAccessStream.h"

RandomAccessStream::RandomAccessStream() {}

int RandomAccessStream::getPending() {
  return this->getPosition() - this->getLength();
}

void RandomAccessStream::padFile(unsigned __int32 toPad) {
  int length = this->getLength();
  int amount = ((length + toPad - 1) & ~(toPad - 1)) - length;
  for (int i = 0; i < amount; ++i)
    this->writeByte(0);
}

void RandomAccessStream::padFileTo(unsigned __int32 a1, unsigned __int32 a2) {
  int length = this->getLength();
  int amount = a1 - length - a2;
  for (int i = 0; i < amount; ++i)
    this->writeByte(0);
}

void RandomAccessStream::readFrom(int arg1, void *buffer, int length) {
  this->setPosition(arg1);
  this->read(buffer, length);
}

int RandomAccessStream::readIntFrom(int position) {
  this->setPosition(position);
  return this->readInt();
}

void RandomAccessStream::skipPadding(unsigned __int32 paddingAmount) {
  int length = this->getPosition();
  int resultAmount =
      (~(paddingAmount - 1) & (length + paddingAmount - 1)) - length;
  for (int i = 0; i < resultAmount; ++i)
    char temp = this->readByte();
}
