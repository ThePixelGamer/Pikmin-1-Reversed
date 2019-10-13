#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef ATXCOMMANDSTREAM_H
#define ATXCOMMANDSTREAM_H

#include <Atx/AtxStream.h>

class SYSCORE_API AtxCommandStream : public AtxStream
{
public:
    // 0h - vtbl
    // 4h - stream var
    class BaseApp* m_baseApp; // 10h

    AtxCommandStream(BaseApp* app) { this->m_baseApp = app; }
    bool checkCommands();
};

#endif