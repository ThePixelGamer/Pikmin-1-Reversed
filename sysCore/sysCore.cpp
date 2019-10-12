#include "sysCore.h"
#include "AyuStack.h"
#include "System/System.h"

SYSCORE_API HINSTANCE hInstance;
SYSCORE_API HINSTANCE sysHInst;
SYSCORE_API Stream *sysCon;
SYSCORE_API class Stream *errCon;
SYSCORE_API HWND sysCurrWnd;
SYSCORE_API int glnHeight = 640;
SYSCORE_API int glnWidth = 480;

void SYSNEWPRINT(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  char dest[1024];

  if (sysCon) {
    if ("sysNew")
      sysCon->print("%s: ", "sysNew");
    vsprintf(dest, fmt, args);
    if (strlen(dest)) {
      sysCon->write(dest, strlen(dest));
    }
  }
}

void SYSNEWHALT(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  char dest[1024];
  vsprintf(dest, fmt, args);
  System::halt("c:\\development\\dolphinpiki\\syscore\\sysnew.cpp", 6, dest);
  // file, line, error
}

BOOL __stdcall DllMain(HINSTANCE hinstDLL, DWORD fdwReason,
                       LPVOID lpvReserved) {
  if (fdwReason == 1)
    hInstance = hinstDLL;
  return TRUE;
}

void *operator new(size_t size) {
  void *returnValue = nullptr;
  if (gsys->heapNum >= 0) {
    AyuHeap heap = gsys->heaps[gsys->heapNum];
    if (!size)
      SYSNEWPRINT("trying to allocate %d byte on heap\n");
    returnValue = static_cast<void *>(heap.push(size));
    if (!returnValue)
      SYSNEWHALT("new[] %d failed in heap '%s'", size, heap.name);
    for (int i = 0; i < size; i++)
      static_cast<int *>(returnValue)[i] = NULL;
  } else {
    returnValue = GlobalAlloc(GMEM_FIXED, size);
    if (!returnValue)
      SYSNEWHALT("new[] %d failed", size);
  }
  return returnValue;
}

void *operator new[](size_t size) {
  void *returnValue = nullptr;
  if (gsys->heapNum >= 0) {
    AyuHeap heap = gsys->heaps[gsys->heapNum];
    if (!size)
      SYSNEWPRINT("trying to allocate %d byte on heap\n");
    returnValue = static_cast<void *>(heap.push(size));
    if (!returnValue)
      SYSNEWHALT("new[] %d failed in heap '%s'", size, heap.name);
    for (int i = 0; i < size; i++)
      static_cast<int *>(returnValue)[i] = NULL;
  } else {
    returnValue = GlobalAlloc(GMEM_FIXED, size);
    if (!returnValue)
      SYSNEWHALT("new[] %d failed", size);
  }
  return returnValue;
}

void *operator new[](size_t size, size_t align) {
  return reinterpret_cast<void *>(((int)new char[align + size] + align - 1) &
                                  ~(align - 1));
}

void operator delete(void *toDelete) {
  if (gsys->heapNum < 0)
    GlobalFree(toDelete);
}

void operator delete[](void *toDelete) {
  if (gsys->heapNum < 0)
    GlobalFree(toDelete);
}
