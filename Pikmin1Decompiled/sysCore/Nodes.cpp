#include "Nodes.h"

//////////////////////////////////////////////////////////////////////
// ANode class functions
//////////////////////////////////////////////////////////////////////

void ANode::genAge(AgeServer* tmp) {}
void ANode::genAgeNode(AgeServer* tmp) {}
int ANode::getAgeNodeType() { return 0; }

//////////////////////////////////////////////////////////////////////
// CoreNode class functions
//////////////////////////////////////////////////////////////////////

CoreNode::CoreNode(char* name) {
	this->initCore(name);
}

int CoreNode::getAgeNodeType() {
	return 2;
}

CoreNode* CoreNode::Next() {
	return this->next;
}

void CoreNode::Next(CoreNode* set) {
	this->next = set;
}

CoreNode* CoreNode::Child() {
	return this->child;
}

void CoreNode::Child(CoreNode* set) {
	this->child = set;
}

char* CoreNode::Name() {
	return this->name;
}

CoreNode* CoreNode::Parent() {
	return this->parent;
}

void CoreNode::initCore(char* nme) {
	this->parent = 0;
	this->next = 0;
	this->child = 0;
	this->setName(nme);
}

void CoreNode::setName(char* nme) {
	this->name = nme;
}

void CoreNode::add(CoreNode* toAdd) {
	CoreNode* temp = this->child;

	if (temp)
	{
		while (temp->next)
			temp = temp->next;
		temp->next = toAdd;
	}
	else {
		this->child = toAdd;
	}

	toAdd->parent = this;
}

void CoreNode::del()
{
	if (this->parent)
	{
		CoreNode* parChild = this->parent->child;
		CoreNode* oldChild = 0;
		while (parChild)
		{
			if (parChild == this)
			{
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

int CoreNode::getChildCount()
{
	int count;
	for (CoreNode* temp = this->child; temp; temp = temp->next)
		count++;
	return count;
}

//////////////////////////////////////////////////////////////////////
// Node class functions
//////////////////////////////////////////////////////////////////////

Node::Node(char* name) : CoreNode(name) {
	/*this->init(name)*/
}

void Node::update() {
	Node* i = static_cast<Node*>(this->child);
	while (i) {
		if (i->getFlag(1)) {
			i->concat();
			i->update();
		}
		i = static_cast<Node*>(this->next);
	}
}

void Node::draw(Graphics&) {

}

void Node::render(Graphics&) {

}

void Node::concat() {

}

void Node::concat(VQS&) {

}

void Node::concat(SRT&) {

}

void Node::concat(Matrix4f&) {

}

void Node::getModelMatrix() {

}

bool Node::getFlag(int f) {
	return (f & this->flags) != 0;
}

//////////////////////////////////////////////////////////////////////
// NodeMgr class functions
//////////////////////////////////////////////////////////////////////

SYSCORE_API NodeMgr * nodeMgr;

NodeMgr::NodeMgr() {
	unk = 0;
}

CoreNode* NodeMgr::findNode(char* a1, CoreNode * a2) {
	unkNode = 0;
	foundNode = 0;
	if (!a2)
		a2 = this->firstNode();
	this->recFindNode(a2, a1);
	return unkNode;
}

CoreNode* NodeMgr::firstNode() {
	return &this->firstnode;
}

void NodeMgr::recFindNode(CoreNode * toFind, char* name) {
	if (!foundNode) {
		for (CoreNode* i = toFind; i; i = i->Next()) {
			if (!strcmp(name, i->name)) {
				foundNode = 1;
				unkNode = i;
				return;
			}
			if (i->child)
				this->recFindNode(i->child, name);
		}
	}
}