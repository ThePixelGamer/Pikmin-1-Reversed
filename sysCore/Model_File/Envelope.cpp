#include "Envelope.h"

Envelope::Envelope() {
  this->m_indicesCount = 0;
  this->m_indices = NULL;
  this->m_weights = NULL;
}

void Envelope::read(RandomAccessStream &stream) {
  this->m_indicesCount = stream.readShort();
  // Clever way of allocating memory, do it all in 1 go for both arrays!
  void *allocMem = operator new((sizeof(int) + sizeof(float)) *
                                this->m_indicesCount);
  this->m_indices = static_cast<int *>(allocMem);
  // The weights section of the array starts after the indices, so set the array
  // ptr to after the indices
  this->m_weights = &static_cast<float *>(allocMem)[this->m_indicesCount];

  for (int i = 0; i < this->m_indicesCount; i++) {
    this->m_indices[i] = stream.readShort();
    this->m_weights[i] = stream.readFloat();
  }
}

void Envelope::write(RandomAccessStream &stream) {
  stream.writeInt(this->m_indicesCount);
  for (int i = 0; i < this->m_indicesCount; i++) {
    stream.writeInt(this->m_indices[i]);
    stream.writeFloat(this->m_weights[i]);
  }
}
