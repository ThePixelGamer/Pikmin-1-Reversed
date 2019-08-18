#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef IDELEGATE_H
#define IDELEGATE_H

class IDelegate {
public:
    virtual void invoke() = 0;
};

template <typename Param0>
class IDelegate1 {
public:
    virtual void invoke(Param0 param) = 0;
};

template <typename Param0, typename Param1>
class IDelegate2 {
public:
    virtual void invoke(Param0 param0, Param1 param1) = 0;
};

template <class T, class Method>
class Callback : public IDelegate {
public:
    T target;
    Method op;

	Callback(T trg, Method method) {
		target = trg;
		op = method;
	}

	virtual void invoke() {
		(target->*op)();
	}
};

#endif
