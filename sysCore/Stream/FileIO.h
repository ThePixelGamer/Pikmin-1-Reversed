#pragma once

#ifndef FILEIO_H
#define FILEIO_H

//
#include "RandomAccessStream.h"
#include <stdio.h>
//

// Technically a stream class, so its allowed in the Stream folder,
// only ever used in System::openFile/System::createFile
class fileIO : public RandomAccessStream {
public:
  // 0h - vtable
  //(Stream: 4h)
  FILE *m_fStream;    // 8h
  int m_fPtrPosition; // Ch
  int m_fileSize;     // 10h

  fileIO(FILE *fpointer, char *cwd);

  virtual int getPosition();
  virtual void read(void *buf, int count);
  virtual void write(void *buf, int count);
  virtual int getPending();
  virtual int getAvailable();
  virtual void close();
  virtual void setPosition(int offset);
};

#endif