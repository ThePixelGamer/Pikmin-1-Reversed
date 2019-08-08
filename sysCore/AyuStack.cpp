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
		if ( &this->m_unk2[-*this->m_unk1] != this->m_unk1 )
			haltAyuStack("trashed memory stack (%s)\n", this->name);
}


int AyuStack::getFree() {
	return this->m_size - this->m_used;
}

int AyuStack::getMaxFree() {
	int ret; // [esp+4Ch] [ebp-8h]
	
	if ( this->m_size - this->m_used - 8 > 0 )
		ret = this->m_size - this->m_used - 8;
	else
		ret = 0;
	return ret;
}

int AyuStack::getSize() {
	return this->m_size;
}

int AyuStack::getTopUsed() {
	return m_topSize - m_topFree;
}

int AyuStack::getUsed() {
	return this->m_used;
}

void AyuStack::inactivate() {
	this->active = false;
}

void AyuStack::pop() {
	if (this->m_allocType == 2)
	{
		int used = 2; // *(this->m_unk2 - 2);
		this->m_used -= used;
		//this->m_unk2 = this->m_unk2 - used;
	}
	else
	{
		int used = 2;
		this->m_used -= used;
		this->m_topFree += used;
	}
}

char* AyuStack::push(int toPush) {
	if (!toPush)
		toPush = 1;
	if (toPush & 7)
		toPush = (toPush + 7) & 0xFFFFFFF8;

	int unk = toPush + 8;
	if (this->m_allocType == 2)
	{
		// this makes me think m_unk2 is the top of the stack
		if (this->m_unk2[unk] <= m_topFree)
		{
			char* unused = this->m_unk2;
			int unk2;
			char* top_maybe;
			if (this->m_unk2 == this->m_unk1)
			{
				unk2 = 0;
				top_maybe = this->m_unk2;
			}
			else
			{
				unk2 = *(this->m_unk2 - 2);
				top_maybe = this->m_unk2 - 8;
			}
			
			this->m_used += unk;
			this->m_unk2 = (this->m_unk2 + unk);
			*(this->m_unk2 - 2) = unk2 + unk;
			this->checkStack();
			return top_maybe;
		}
		else
			return 0;
	}
	else if ((this->m_topFree - unk) >= *this->m_unk2)
	{
		this->m_used += unk;
		this->m_topFree -= unk;
		//what *this->m_topFree = unk;
		return this->m_topFree + 8;
	}
	else
		return 0;
}