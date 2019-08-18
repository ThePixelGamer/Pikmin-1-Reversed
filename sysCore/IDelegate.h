#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef IDELEGATE_H
#define IDELEGATE_H

class IDelegate {
public:


	IDelegate();

};

template<typename T>
class IDelegate1 {
public:
	IDelegate1();

};

template<typename E, typename M>
class IDelegate2 {
public:
	IDelegate2(E, M);

};

#endif
