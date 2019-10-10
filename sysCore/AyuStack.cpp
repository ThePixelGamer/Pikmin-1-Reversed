// AyuStack.cpp: implementation of the AyuStack class.
//
//////////////////////////////////////////////////////////////////////

#include "AyuStack.h"
#include <stdarg.h>

#include "System/System.h"

void haltAyuStack(char* fmt, ...) {
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
	return (this->active) 
		? *this->top != 0x12345678 
		: false;
}

void AyuStack::checkStack() {
	if (this->m_allocType & 2)
		//TODO: line below is wrong, fix!
		if (&this->sp[-*this->top] != this->top)
			haltAyuStack("trashed memory stack (%s)\n", this->name);
}

void AyuStack::create(char* nme, int allocType, void* allocMem, int size, bool overflow) {
	this->m_allocType = allocType;
	this->active = true;
	this->name = nme;
	this->top = static_cast<unsigned __int32*>(allocMem);
	this->m_topSize = reinterpret_cast<int>(this->top) + size;
	this->m_size = m_topSize - reinterpret_cast<int>(this->top);
	this->overflowProtect = overflow;
	if(this->overflowProtect)
		*this->top = 0x12345678;
	this->reset();
}

int AyuStack::getFree() {
	return this->m_size - this->m_used;
}

int AyuStack::getMaxFree() {
	int ret; // [esp+4Ch] [ebp-8h]

	if (this->m_size - this->m_used - 8 > 0)
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
		int used = 2; // *(this->sp - 2);
		this->m_used -= used;
		//this->sp = this->sp - used;
	}
	else
	{
		int used = 2;
		this->m_used -= used;
		this->m_topFree += used;
	}
}

/*
unsigned __int32* AyuStack::push(int toPush) {
	if (!toPush)
		toPush = 1;
	if (toPush & 7)
		toPush = (toPush + 7) & 0xFFFFFFF8;

	int unk = toPush + 8;
	if (this->m_allocType == 2) {
		// this makes me think sp is the top of the stack
		if (this->sp[unk] <= m_topFree) {
			unsigned __int32* unused = this->sp;
			int unk2;
			unsigned __int32* top_maybe;
			if (this->sp == this->sp) {
				unk2 = 0;
				top_maybe = this->sp;
			}
			else {
				unk2 = *(this->sp - 2);
				top_maybe = this->sp - 8;
			}

			this->m_used += unk;
			this->sp = (this->sp + unk);
			*(this->sp - 2) = unk2 + unk;
			this->checkStack();
			return top_maybe;
		}
		else
			return 0;
	}
	else if ((this->m_topFree - unk) >= *this->sp)
	{
		this->m_used += unk;
		this->m_topFree -= unk;
		//what *this->m_topFree = unk;
		return this->m_topFree + 8; //fix this
	}
	else
		return 0;
}
*/

void AyuStack::reset(int allocType) {
	if (allocType & 2)
	{
		int prevAllocType = this->setAllocType(allocType);
		gsys->invalidateObjs(*this->top, *this->sp);
		while (this->sp != this->top)
			this->pop();
		this->setAllocType(prevAllocType);
	}
	if (allocType & 1)
	{
		int prevAllocType = this->setAllocType(allocType);
		gsys->invalidateObjs(this->m_topFree, this->m_topSize);
		while (this->m_topFree != this->m_topSize)
			this->pop();
		this->setAllocType(prevAllocType);
	}
}

void AyuStack::reset()
{
	this->sp = this->top;
	this->m_topFree = this->m_topSize;
	this->m_used = 0;
}

int AyuStack::setAllocType(int allocType)
{
	int prev = this->m_allocType;
	this->m_allocType = allocType;
	return prev;
}