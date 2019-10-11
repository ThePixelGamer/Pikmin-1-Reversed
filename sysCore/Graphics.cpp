#include "Graphics.h"

void PRINTGRAPHICS(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  char dest[1024];

  if (sysCon) {
    if ("Graphics")
      sysCon->print("%s: ", "Graphics");
    vsprintf(dest, fmt, args);
    if (strlen(dest)) {
      sysCon->write(dest, strlen(dest));
    }
  }
}

Graphics::Graphics() {
  PRINTGRAPHICS("dgxgraphics constructor\n");
  this->m_unk1 = 0;
  for (int i = 0; i < 4096; ++i) {
    unused[i] = sin(i / 4096.0 * TAU);
    unused2[i] = cos(i / 4096.0 * TAU);
  }

  this->m_unkColour2.set(0, 0, 48, 0xFF);
}

void Graphics::videoReset() {}
void Graphics::setVerticalFilter(char *a2) {}
void Graphics::getVerticalFilter(unsigned __int8 *a2) {}
unsigned __int8 *Graphics::getDListPtr() { return 0; }
unsigned __int32 Graphics::getDListRemainSize() { return 0; }