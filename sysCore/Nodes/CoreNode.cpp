#include "CoreNode.h"
#include "../AgeServer.h"
#include "../Atx/AtxFileStream.h"
#include "../IDelegate.h"
#include "../sysCore.h"

void NODEPRINT(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  char dest[1024];

  if (sysCon) {
    if ("Node")
      sysCon->print("%s: ", "Node");
    vsprintf(dest, fmt, args);
    if (strlen(dest)) {
      sysCon->write(dest, strlen(dest));
    }
  }
}

CoreNode::CoreNode(char *name) { this->initCore(name); }

void CoreNode::genAge(AgeServer &server) {
  server.StartSection("Node", true);
  server.StartGroup("Node");

  IDelegate1<AgeServer &> *loadButton =
      new Callback1<CoreNode *, void (CoreNode::*)(AgeServer &), AgeServer &>(
          this, &CoreNode::genRead);
  server.NewButton("Load", loadButton, 120);

  IDelegate1<AgeServer &> *saveButton =
      new Callback1<CoreNode *, void (CoreNode::*)(AgeServer &), AgeServer &>(
          this, &CoreNode::genWrite);
  server.NewButton("Save", saveButton, 120);

  server.EndGroup();
  server.EndSection();
}

struct String_Unk : public String {
  String_Unk() : String() { this->init(128); }
};

void CoreNode::genRead(AgeServer &server) {
  String_Unk unkString;
  if (server.getOpenFilename(unkString, "All files (*.*)|*.*")) {
    AtxFileStream stream;
    NODEPRINT("Trying to open file '%s'\n", unkString.m_string);
    if (stream.open(unkString.m_string, true)) {
      NODEPRINT("opened file ...\n");
    }
  }
}

int CoreNode::getAgeNodeType() { return 2; }

CoreNode *CoreNode::Next() { return this->next; }

void CoreNode::Next(CoreNode *set) { this->next = set; }

CoreNode *CoreNode::Child() { return this->child; }

void CoreNode::Child(CoreNode *set) { this->child = set; }

char *CoreNode::Name() { return this->name; }

CoreNode *CoreNode::Parent() { return this->parent; }

void CoreNode::initCore(char *nme) {
  this->parent = 0;
  this->next = 0;
  this->child = 0;
  this->setName(nme);
}

void CoreNode::setName(char *nme) { this->name = nme; }

void CoreNode::add(CoreNode *toAdd) {
  CoreNode *temp = this->child;

  if (temp) {
    while (temp->next)
      temp = temp->next;
    temp->next = toAdd;
  } else {
    this->child = toAdd;
  }

  toAdd->parent = this;
}

void CoreNode::del() {
  if (this->parent) {
    CoreNode *parChild = this->parent->child;
    CoreNode *oldChild = 0;
    while (parChild) {
      if (parChild == this) {
        if (oldChild)
          oldChild->next = parChild->next;
        else
          this->parent->child = parChild->next;
        this->next = 0;
        this->parent = 0;
        return;
      }
      oldChild = parChild;
      parChild = parChild->next;
    }
  }
}

int CoreNode::getChildCount() {
  int count;
  for (CoreNode *temp = this->child; temp; temp = temp->next)
    count++;
  return count;
}

char *CoreNode::getName() { return this->name; }