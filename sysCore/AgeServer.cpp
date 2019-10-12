#include "AgeServer.h"
#include "Colour.h"
#include "System/System.h"
#include "sysCore.h"

void AGEPRINT(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  char dest[1024];

  if (sysCon) {
    if ("Age")
      sysCon->print("%s: ", "Age");
    vsprintf(dest, fmt, args);
    if (strlen(dest)) {
      sysCon->write(dest, strlen(dest));
    }
  }
}

void AGEHALT(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  char dest[1024];
  vsprintf(dest, fmt, args);
  System::halt("C:\\Development\\DolphinPiki\\sysCommon\\age.cpp", 7, dest);
  // file, line, error
}

AgeServer::AgeServer() {}

// END

void AgeServer::Done() { this->writeInt(200); }

void AgeServer::EndBitGroup() { this->writeInt(0); }

void AgeServer::EndGroup() { this->writeInt(303); }

void AgeServer::EndNode() { this->writeInt(200); }

void AgeServer::EndOptionBox() { this->writeInt(0); }

void AgeServer::EndSection() {
  this->writeInt(301);
  this->m_sectionStarted = false;
}

// NEW

void AgeServer::NewBit(char *str, unsigned __int32 a2, unsigned __int32 a3) {
  this->writeInt(1);
  this->writeString(str);
  this->writeInt(a2);
  this->writeInt(a3);
}

void AgeServer::NewButton(char *name, IDelegate *callback, int unk) {
  this->writeInt(105);
  this->writeString(name);
  this->writeInt(unk);
  this->writeInt(0);
  this->writeInt(reinterpret_cast<int>(callback));
}

void AgeServer::NewButton(char *name, IDelegate1<AgeServer &> *callback,
                          int unk) {
  this->writeInt(105);
  this->writeString(name);
  this->writeInt(unk);
  this->writeInt(1);
  this->writeInt(reinterpret_cast<int>(callback));
}

void AgeServer::NewEditor(char *name, class AyuImage *image, bool unk) {
  this->writeInt(102);
  this->writeString(name);
  if (unk)
    this->writeProp(IMAGE_PROP, image);
  else
    this->writeProp(STRING_PROP, image);
}

void AgeServer::NewEditor(char *unk, Colour *col) {
  this->writeInt(102);
  this->writeString(unk);
  this->writeProp(COLOUR_PROP, col);
}

void AgeServer::NewEditor(char *unk, char *unk2, int unk3) {
  this->writeInt(102);
  this->writeString(unk);
  this->writeProp(CHAR_PTR_PROP, unk2);
  this->writeInt(unk3 - 1);
}

void AgeServer::NewEditor(char *unk, char *unk2, int unk3, int unk4, int unk5) {
  this->writeInt(102);
  this->writeString(unk);
  this->writeProp(CHAR_PROP, unk2);
  this->writeInt(unk3);
  this->writeInt(unk4);
  this->writeInt(unk5);
}

void AgeServer::NewEditor(char *unk, float *unk2, float unk3, float unk4,
                          int unk5) {
  this->writeInt(102);
  this->writeString(unk);
  this->writeProp(FLOAT_PROP, unk2);
  this->writeFloat(unk3);
  this->writeFloat(unk4);
  this->writeInt(unk5);
}

void AgeServer::NewEditor(char *unk, int *unk2, int unk3, int unk4, int unk5) {
  this->writeInt(102);
  this->writeString(unk);
  this->writeProp(INT_PROP, unk2);
  this->writeInt(unk3);
  this->writeInt(unk4);
  this->writeInt(unk5);
}

void AgeServer::NewEditor(char *unk, short *unk2, int unk3, int unk4,
                          int unk5) {
  this->writeInt(102);
  this->writeString(unk);
  this->writeProp(SHORT_PROP, unk2);
  this->writeInt(unk3);
  this->writeInt(unk4);
  this->writeInt(unk5);
}

void AgeServer::NewNodeWindow(char *name) {
  this->writeInt(100);
  this->writeString(name);
}

void AgeServer::NewOption(char *name, int optionIndex) {
  this->writeInt(1);
  this->writeString(name);
  this->writeInt(optionIndex);
}

void AgeServer::NewPropWindow(char *name, unsigned __int32 window) {
  this->writeInt(104);
  this->writeString(name);
  this->writeInt(window);
}

void AgeServer::NewViewer(char *name, float *prop) {
  this->writeInt(107);
  this->writeString(name);
  this->writeProp(FLOAT_PROP, prop);
}

void AgeServer::NewViewer(char *name, int *prop) {
  this->writeInt(107);
  this->writeString(name);
  this->writeProp(INT_PROP, prop);
}

void AgeServer::NewNode(char *name, ANode *node) {
  this->writeInt(101);
  this->writeInt(reinterpret_cast<int>(node));
  this->writeString(name);
  this->writeInt(node->getAgeNodeType());
}

void AgeServer::setOnChange(IDelegate *d) {
  this->writeInt(207);
  this->writeInt(0);
  this->writeInt(reinterpret_cast<int>(d));
}

void AgeServer::setOnChange(IDelegate1<AgeServer &> *d) {
  this->writeInt(207);
  this->writeInt(1);
  this->writeInt(reinterpret_cast<int>(d));
}

void AgeServer::setSectionRefresh(IDelegate1<AgeServer &> *d) {
  this->writeInt(208);
  this->writeInt(reinterpret_cast<int>(d));
}

void AgeServer::update() {
	// need to do this function
  bool hasDataLeft = false;
  while (true) {
    if (this->getPending()) {
      hasDataLeft = true;
      const int identifier = this->readInt();
      //switch (identifier) {
        // case
      //}
    }
  }
}

// WRITE

void AgeServer::writeProp(PROP_TYPE type, void *buffer) {
  this->writeInt((int)type);
  this->writeInt((int)buffer);
  this->writePropValue(type, buffer);
}

void AgeServer::writePropValue(PROP_TYPE type, void *buffer) {
  switch (type) {
  case CHAR_PROP:
    this->writeInt(*static_cast<int *>(buffer));
    break;
  case SHORT_PROP:
    this->writeInt(*static_cast<int *>(buffer));
    break;
  case INT_PROP:
    this->writeInt(*static_cast<int *>(buffer));
    break;
  case FLOAT_PROP:
    this->writeFloat(*static_cast<float *>(buffer));
    break;
  case COLOUR_PROP:
    this->writeInt((*static_cast<Colour *>(buffer)).R);
    this->writeInt((*static_cast<Colour *>(buffer)).G);
    this->writeInt((*static_cast<Colour *>(buffer)).B);
    this->writeInt((*static_cast<Colour *>(buffer)).A);
    break;
  case UNK7:
  case UNK9:
	  return;
  case CHAR_PTR_PROP:
	  this->writeString(static_cast<char*>(buffer));
  default:
    AGEHALT("Unsupported PropType");
	return;
  }
  return;
}

bool AgeServer::Open() {
  AGEPRINT("!!!!! Opening Age server\n");
  if (this->open("age", 3)) {
    this->m_sectionStarted = false;
    return true;
  } else {
    AGEPRINT("cant open AgeServer\n");
    return false;
  }
}

void AgeServer::RefreshNode() { this->writeInt(402); }

void AgeServer::RefreshSection() { this->writeInt(403); }

void AgeServer::StartBitGroup(char *name, unsigned __int32 *prop, int unk) {
  this->writeInt(102);
  this->writeString(name);
  this->writeProp(UNK7, 0);
  this->writeProp(INT_PROP, prop);
  this->writeInt(unk);
}

void AgeServer::StartBitGroup(char *name, unsigned __int8 *prop, int unk) {
  this->writeInt(102);
  this->writeString(name);
  this->writeProp(UNK7, 0);
  this->writeProp(CHAR_PROP, prop);
  this->writeInt(unk);
}

bool AgeServer::getOpenFilename(String &str, char *filter) {
  this->writeInt(404);
  if (filter) {
    AGEPRINT("filter length = %d\n", strlen(filter));
    this->writeString(filter);
    ;
  } else
    this->writeString("All (*.*)|*.*");

  this->readString(str);
  return str.getLength() != 0;
}

bool AgeServer::getSaveFilename(String &str, char *filter) {
  this->writeInt(405);
  if (filter)
    this->writeString(filter);
  else
    this->writeString("All (*.*)|*.*");

  this->readString(str);
  return str.getLength() != 0;
}

void AgeServer::readPropValue(PROP_TYPE type, void *buffer) {
  switch (type) {
  case CHAR_PROP: {
    char *tempBuffer = static_cast<char *>(buffer);
    *tempBuffer = static_cast<char>(this->readInt());
    break;
  }
  case SHORT_PROP: {
    short *tempBuffer = static_cast<short *>(buffer);
    *tempBuffer = static_cast<short>(this->readInt());
    break;
  }
  case INT_PROP: {
    int *tempBuffer = static_cast<int *>(buffer);
    *tempBuffer = this->readInt();
    break;
  }
  case FLOAT_PROP: {
    float *tempBuffer = static_cast<float *>(buffer);
    *tempBuffer = this->readFloat();
    break;
  }
  case COLOUR_PROP: {
    Colour *tempBuffer = static_cast<Colour *>(buffer);
    tempBuffer->R = this->readInt();
    tempBuffer->G = this->readInt();
    tempBuffer->B = this->readInt();
    tempBuffer->A = this->readInt();
    break;
  }
  case CHAR_PTR_PROP: {
    // unused
    int *unused = static_cast<int *>(buffer);
    this->readString(static_cast<char *>(buffer), 10000);
    break;
  }
  default:
    AGEHALT("Unsupported PropType");
    return;
  }
}

void AgeServer::StartSection(char *name, bool unk) {
  this->writeInt(300);
  this->writeInt(static_cast<int>(unk));
  this->writeString(name);
  this->m_sectionStarted = true;
}

void AgeServer::close() { AtxStream::close(); }

void AgeServer::StartGroup(char *name) {
  this->writeInt(302);
  this->writeString(name);
}

void AgeServer::StartOptionBox(char *name, int *prop, int unk) {
  this->writeInt(102);
  this->writeString(name);
  AGEPRINT("new optionbox : %08x\n", prop);
  this->writeProp(UNK9, 0);
  this->writeProp(INT_PROP, prop);
  this->writeInt(unk);
}

void AgeServer::StartOptionBox(char *name, unsigned __int16 *prop, int unk) {
  this->writeInt(102);
  this->writeString(name);
  this->writeProp(UNK9, 0);
  this->writeProp(SHORT_PROP, prop);
  this->writeInt(unk);
}

void AgeServer::StartOptionBox(char *name, unsigned __int8 *prop, int unk) {
  this->writeInt(102);
  this->writeString(name);
  this->writeProp(UNK9, 0);
  this->writeProp(CHAR_PROP, prop);
  this->writeInt(unk);
}
