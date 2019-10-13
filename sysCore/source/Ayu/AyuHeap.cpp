#include <Ayu/AyuHeap.h>

void AyuHeap::init(char* name, int allocType, void* allocMem, int size)
{
    this->create(name, allocType, allocMem, size, false);
    this->unk = 0;
}
