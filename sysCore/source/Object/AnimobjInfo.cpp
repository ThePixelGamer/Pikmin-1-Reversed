#include <Object/AnimobjInfo.h>

#include <Anim/AnimData.h>

AnmobjInfo::AnmobjInfo() { this->animData = 0; }

void AnmobjInfo::detach() { animData->detach(); }