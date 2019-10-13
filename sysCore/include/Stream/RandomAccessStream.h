#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef RAS_H
#define RAS_H

#include <Stream/Stream.h>

class SYSCORE_API RandomAccessStream : public Stream
{
public:
    // 0h - vtable
    // (Stream: 4h)

    RandomAccessStream();

    // (Stream VTable 0h - 4Ch)
    virtual int getPending();                                // 50h
    virtual int getPosition() { return 0; }                  // 54h
    virtual void setPosition(int) {}                         // 58h
    virtual int getLength() { return this->getAvailable(); } // 5Ch

    void padFile(unsigned __int32 toPad);
    void padFileTo(unsigned __int32 a1, unsigned __int32 a2);
    void readFrom(int arg1, void* buffer, int length);
    int readIntFrom(int position);
    void skipPadding(unsigned __int32 paddingAmount);
};

#endif
