#pragma once

#ifndef DEBUGSTREAM_H
#define DEBUGSTREAM_H

//
#include "../UI/UIWindow.h"
#include "RandomAccessStream.h"
//

// Used in System for System::createDebugStream
class DebugStream : public Stream // not exported
{
public:
  // 0h - vtbl
  // 4h - stream var
  int m_written;                  // 8h
  int m_optionCount;              // Ch
  char m_currentString[256];      // 10h
  RandomAccessStream *m_RAStream; // 110h
  UIWindow *m_window;             // 114h

  DebugStream(UIWindow *window);

  void writeChar(char toWrite);

  virtual void write(void *buf, int length);
  virtual void flush();
};

#endif