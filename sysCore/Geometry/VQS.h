#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef VQS_H
#define VQS_H

class VQS {
public:
	VQS();

};

#endif