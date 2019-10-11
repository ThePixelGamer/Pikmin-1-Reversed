#include "DebugStream.h"
#include "../System/System.h"

DebugStream::DebugStream(UIWindow *window) {
  this->m_written = 0;
  this->m_optionCount = 0;

  this->m_window = new UIWindow(window, 15, 0x50200140, 512, false);
  this->m_window->sizeWindow(window->m_client.width(),
                             window->m_client.height(), 0);
  this->m_window->createWindow("ListBox", 0, 0);
  WPARAM obj = (WPARAM)GetStockObject(DEFAULT_GUI_FONT);
  SendMessage(this->m_window->m_hWnd, WM_SETFONT, obj, 0);
  this->m_RAStream = gsys->createFile("../log.txt", true);
}

void DebugStream::writeChar(char toWrite) {
  if (this->m_written >= 255)
    this->flush();

  this->m_currentString[this->m_written] = toWrite;
  this->m_written++;
}

void DebugStream::write(void *buffer, int length) {
  for (int i = 0; i < length; i++) {
    char currentChar = static_cast<char *>(buffer)[i];
    if (currentChar == '\n')
      this->flush();

    else if (currentChar == '\t') {
      this->writeChar(' ');
      this->writeChar(' ');
    }

    else
      this->writeChar(currentChar);
  }
}

void DebugStream::flush() {
  this->m_currentString[this->m_written] = 0;
  if (this->m_window) {
    if (gsys->m_debugStreamUnk == nullptr) {
      SendMessage(this->m_window->m_hWnd, LB_ADDSTRING, NULL,
                  (LPARAM)this->m_currentString);
      SendMessage(this->m_window->m_hWnd, LB_SETCURSEL, this->m_optionCount++,
                  NULL);

      if (this->m_RAStream) { // has file open
        char newline[2];
        strcpy(newline, "\n");
        this->m_RAStream->write(this->m_currentString,
                                strlen(this->m_currentString));
        this->m_RAStream->write(newline, strlen(newline));
      }
    }
  }
  this->m_written = 0;
}