#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef BUFFEREDSTREAM_H
#define BUFFEREDSTREAM_H

#include "RandomAccessStream.h"

// TODO
class SYSCORE_API BufferedInputStream : public RandomAccessStream {
public:
  int m_position;
  Stream *m_stream;

  BufferedInputStream(){};
  BufferedInputStream(Stream *stream, unsigned __int8 *buf, int bufSize) {
    this->init(stream, buf, bufSize);
  };

  void close() {}
  void fillBuffer() {}
  int getPending() { return NULL; }
  int getPosition() { return m_position; }
  void init(Stream *stream, unsigned __int8 *buf, int bufSize) {}
  void open(Stream *stream) {
    // this->dword14 = 0;
    this->m_position = 0;
    // this->dword10 = 0;
    this->m_stream = stream;
  }
  void read(void *buffer, int size) {}
  void resetBuffer() {}
};

#endif