#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef SRT_H
#define SRT_H


class SRT {
public:
	SRT();

};

#endif