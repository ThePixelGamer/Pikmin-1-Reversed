#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef OPTIONBOX_H
#define OPTIONBOX_H

#include "ComboBox.h"

class SYSCORE_API OptionBox : public ComboBox {
public:
	//vtable 0h
	//(CoreNode: 4h-10h)
	//(Node: 14h-1Ch)
	//(UIFrame: 20h-40h)
	//(UIWindow: 50h-84h)
	//(ComboBox: 88h-8Ch)

	OptionBox(UIWindow*, int, int, int, bool);

	virtual void selectionChanged(int);
	virtual int processMessage(HWND, unsigned int, WPARAM, long);
};

#endif