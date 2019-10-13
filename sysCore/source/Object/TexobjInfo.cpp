#include <Model/DispList.h>
#include <Object/TexobjInfo.h>
#include <Texture/Texture.h>

TexobjInfo::TexobjInfo() { this->texData = 0; }

void TexobjInfo::detach() { texData->detach(); }
