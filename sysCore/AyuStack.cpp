// AyuStack.cpp: implementation of the AyuStack class.
//
//////////////////////////////////////////////////////////////////////

#include "AyuStack.h"
#include <stdarg.h>

void haltAyuStack(char * fmt, ...)
{
	char Dest; // [esp+4Ch] [ebp-804h]
	va_list va; // [esp+85Ch] [ebp+Ch]
	
	va_start(va, fmt);
	vsprintf(&Dest, fmt, va);
	System::halt("c:\\development\\dolphinpiki\\syscommon\\ayustack.cpp", 7, &Dest);
}

AyuStack::AyuStack() {
	this->active = false;
}

bool AyuStack::checkOverflow() {
	if (this->active)
		return *this->m_unk1 != 0x12345678;
	else
		return false;
}

void AyuStack::checkStack() {
	if (this->m_allocType & 2)
		if ( &this->m_unk2[-*(this->m_unk2 - 8)] != this->m_unk1 )
			haltAyuStack("trashed memory stack (%s)\n", this->name);
}
