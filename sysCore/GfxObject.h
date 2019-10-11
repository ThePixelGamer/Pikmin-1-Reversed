#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef GfxObject_H
#define GfxObject_H

class SYSCORE_API GfxObject {
public:
  virtual void attach();
  virtual void detach();
};

#endif