#include <Ayu/AyuStack.h>
#include <System/System.h>
#include <stdarg.h>

void AYUSTACKHALT(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char dest[1024];
    vsprintf(dest, fmt, args);
    System::halt("c:\\development\\dolphinpiki\\syscommon\\ayustack.cpp", 7, dest);
    // file, line, error
}

AyuStack::AyuStack() { this->active = false; }

bool AyuStack::checkOverflow() { return (this->active) ? *this->top != 0x12345678 : false; }

void AyuStack::checkStack()
{
    if (this->m_allocType & 2)
        // TODO: line below is wrong, fix!
        if (&this->sp[-*this->top] != this->top)
            AYUSTACKHALT("trashed memory stack (%s)\n", this->name);
}

void AyuStack::create(char* nme, int allocType, void* allocMem, int size, bool overflow)
{
    this->m_allocType = allocType;
    this->active = true;
    this->name = nme;
    this->top = static_cast<unsigned __int32*>(allocMem);
    this->m_topSize = reinterpret_cast<int>(this->top) + size;
    this->m_size = m_topSize - reinterpret_cast<int>(this->top);
    this->overflowProtect = overflow;
    if (this->overflowProtect)
        *this->top = 0x12345678;
    this->reset();
}

int AyuStack::getFree() { return this->m_size - this->m_used; }

int AyuStack::getMaxFree()
{
    int maxFree = (this->m_size - this->m_used - 8 > 0) ? this->m_size - this->m_used - 8 : 0;
    return maxFree;
}

int AyuStack::getSize() { return this->m_size; }

int AyuStack::getTopUsed() { return m_topSize - m_topFree; }

int AyuStack::getUsed() { return this->m_used; }

void AyuStack::inactivate() { this->active = false; }

void AyuStack::pop()
{
    if (this->m_allocType == 2)
    {
        int used = 2; // *(this->sp - 2);
        this->m_used -= used;
        // this->sp = this->sp - used;
    }
    else
    {
        int used = 2;
        this->m_used -= used;
        this->m_topFree += used;
    }
}

unsigned __int32* AyuStack::push(int toPush)
{
    if (!toPush)
        toPush = 1;
    if (toPush & 7)
        toPush = (toPush + 7) & 0xFFFFFFF8;

    int unk = toPush + 8;
    if (this->m_allocType == 2)
    {
        // this makes me think sp is the top of the stack
        if (this->sp[unk] <= m_topFree)
        {
            unsigned __int32* unused = this->sp;
            int unk2;
            unsigned __int32* top_maybe;
            if (this->sp == this->sp)
            {
                unk2 = 0;
                top_maybe = this->sp;
            }
            else
            {
                unk2 = *(this->sp - 2);
                top_maybe = (this->sp - 2);
            }

            this->m_used += unk;
            this->sp = (this->sp + unk);
            *(this->sp - 2) = unk2 + unk;
            this->checkStack();
            return top_maybe;
        }
        else
            return nullptr;
    }
    else if ((this->m_topFree - unk) < *this->sp)
    {
        return nullptr;
    }
    else
        this->m_used += unk;
    this->m_topFree -= unk;
    // what *this->m_topFree = unk;
    return reinterpret_cast<unsigned __int32*>(&this->m_topFree + 8); // fix this
}

void AyuStack::reset(int allocType)
{
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
