#include "Node.h"

Node::Node(char *name) : CoreNode(name) { /*this->init(name)*/
}

void Node::update() { // asm matches
  Node *i = static_cast<Node *>(this->child);
  while (i) {
    if (i->getFlag(1)) {
      i->concat();
      i->update();
    }
    i = static_cast<Node *>(this->next);
  }
}

void Node::draw(Graphics &a2) { // asm matches
  for (Node *tmp = static_cast<Node *>(this->child); tmp;
       tmp = static_cast<Node *>(tmp->next)) {
    tmp->draw(a2);
  }
}

void Node::render(Graphics &a2) { // asm matches
  this->draw(a2);
}

void Node::concat() {} // asm matches

void Node::concat(VQS &a2) { // asm matches
  this->concat();
}

void Node::concat(SRT &a2) { // asm matches
  this->concat();
}

void Node::concat(Matrix4f &) { // asm matches
  this->concat();
}

Matrix4f *Node::getModelMatrix() { // asm matches
  return 0;
}

void Node::clearFlag(int a2) { // asm matches
  this->flags &= ~a2;
}

int Node::getFlag(int f) { // asm matches
  return (this->flags & f) != 0;
}

int Node::getFlags() { // asm matches
  return this->flags;
}

int Node::getType() { // asm matches
  return this->type;
}

void Node::init(char *a2) { // asm matches
  this->initCore(a2);
  this->setFlags(3);
  this->dword1c = -1;
}

void Node::setFlag(int a2) { // asm matches
  this->flags |= a2;
}

void Node::setFlag(int a2, bool a3) { // asm matches
  if (a3) {
    this->setFlag(a2);
  } else {
    this->clearFlag(a2);
  }
}

void Node::setFlags(int a2) { // asm matches
  this->flags = a2;
}

void Node::setType(int a2) { // asm matches
  this->type = a2;
}

void Node::togFlag(int a2) { // asm matches
  this->flags ^= a2;
}