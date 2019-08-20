// AyuHeap.cpp: implementation of the AyuHeap class.
//
//////////////////////////////////////////////////////////////////////

#include "AyuHeap.h"

void AyuHeap::init(char* name, int allocType, void* allocMem, int size) {
    this->create(name, allocType, allocMem, size);
}