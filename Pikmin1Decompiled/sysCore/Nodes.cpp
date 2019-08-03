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

//Matrix4f* Node::getModelMatrix() {
//	return new Matrix4f;
//}

bool Node::getFlag(int f) {
	return (f & this->flags) != 0;
}

//////////////////////////////////////////////////////////////////////
// EditNode class functions
//////////////////////////////////////////////////////////////////////

EditNode::EditNode(char* unk) : CoreNode(unk) {}

void EditNode::msgCommand(DataMsg& unk) {}
void EditNode::render2d(Graphics& unk, int& unk1) {}

//////////////////////////////////////////////////////////////////////
// FaceNode class functions
//////////////////////////////////////////////////////////////////////

FaceNode::FaceNode() : CoreNode("face") {}
FaceNode::FaceNode(int unk) : CoreNode("face") {
	this->m_facenode_0  = unk; 
	this->m_facenode_1  = 0; 
	this->m_facenode_2  = 0; 
	this->m_facenode_3  = 0; 
	this->m_facenode_4  = 0; 
	this->m_facenode_5  = 0; 
	this->m_facenode_6  = 0; 
	this->m_facenode_7  = 0; 
	this->m_facenode_8  = 0; 
	this->m_facenode_9  = 0; 
	this->m_facenode_10 = 0;
	this->m_facenode_11 = 0;
	this->m_facenode_12 = 0;
}

//////////////////////////////////////////////////////////////////////
// MemInfoNode class functions
//////////////////////////////////////////////////////////////////////

MemInfoNode::MemInfoNode() : CoreNode("meminfo") {}

//////////////////////////////////////////////////////////////////////
// SRTNode class functions
//////////////////////////////////////////////////////////////////////
/*
SRTNode::SRTNode(char*) : Node() {
	Vector3f pos(0.0, 0.0, 0.0);
	setPosition(pos);

	Vector3f rot(1.0, 1.0, 1.0);
	setRotation(rot);

	Vector3f sc(0.0, 0.0, 0.0);
	setScale(sc);
}

void SRTNode::update();
void SRTNode::concat();
void SRTNode::concat(Matrix4f&);
//Matrix4f* SRTNode::getModelMatrix();

void SRTNode::genAge(AgeServer&);
Vector3f* SRTNode::getPosition();
Vector3f* SRTNode::getRotation();
Vector3f* SRTNode::getScale();
Vector3f* SRTNode::getWorldPosition();
void SRTNode::setPosition(Vector3f&);
void SRTNode::setRotation(Vector3f&);
void SRTNode::setScale(Vector3f&);
void SRTNode::update();*/
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

void NodeMgr::Del(Node * toDelete)
{
	this->unk = 1;
	if (toDelete && toDelete->parent)
	{
		CoreNode * toDeleteChild = toDelete->parent->child;
		
		CoreNode * tempNext = 0;
		while (toDeleteChild)
		{
			if (toDeleteChild == toDelete)
			{
				if (tempNext)
				{
					tempNext->Next(toDeleteChild->Next());
					return;
				}
				toDelete->parent->child = toDeleteChild->Next();
			}
			tempNext = toDeleteChild;
			toDeleteChild = toDeleteChild->Next();
		}
	}
}