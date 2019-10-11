#include "CoreNode.h"
#include "../AgeServer.h"

CoreNode::CoreNode(char* name) {
	this->initCore(name);
}

void CoreNode::genAge(AgeServer& server)
{
	server.StartSection("Node", true);
	server.StartGroup("Node");

	IDelegate1<AgeServer&>* loadButton = new Callback1<CoreNode*, void (CoreNode::*)(AgeServer&), AgeServer&>(this, &CoreNode::genRead);
	server.NewButton("Load", loadButton, 120);

	server.EndGroup();
	server.EndSection();
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

char* CoreNode::getName()
{
	return this->name;
}