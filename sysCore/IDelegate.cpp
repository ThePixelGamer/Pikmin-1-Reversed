#include "IDelegate.h"

//////////////////////////////////////////////////////////////////////
// IDelegate class functions
//////////////////////////////////////////////////////////////////////

template <class T, class Method>
Callback<T, Method>::Callback(T trg, Method method) : target(trg), op(method) {}

template <class T, class Method>
void Callback<T, Method>::invoke() {
    (target->*op)();
}

//////////////////////////////////////////////////////////////////////
// IDelegate1 class functions
//////////////////////////////////////////////////////////////////////

template <class T, class Method, class Param0>
Callback1<T, Method, Param0>::Callback1(T trg, Method method) : target(trg), op(method) {}

template <class T, class Method, class Param0>
void Callback1<T, Method, Param0>::invoke(Param0 param0) {
    (target->*op)(param0);
}

//////////////////////////////////////////////////////////////////////
// IDelegate2 class functions
//////////////////////////////////////////////////////////////////////

template <class T, class Method, class Param0, class Param1>
Callback2<T, Method, Param0, Param1>::Callback2(T trg, Method method) : target(trg), op(method) {}

template <class T, class Method, class Param0, class Param1>
void Callback2<T, Method, Param0, Param1>::invoke(Param0 param0, Param1 param1) {
    (target->*op)(param0, param1);
}