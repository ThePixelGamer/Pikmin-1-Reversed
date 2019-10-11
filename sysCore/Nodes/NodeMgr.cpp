#include "NodeMgr.h"

SYSCORE_API NodeMgr* nodeMgr;

NodeMgr::NodeMgr() {
	unk = 0;
}

NodeMgr::~NodeMgr() {

}

CoreNode* NodeMgr::findNode(char* a1, CoreNode* a2) {
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

void NodeMgr::recFindNode(CoreNode* toFind, char* name) {
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

void NodeMgr::Del(Node* toDelete)
{
	this->unk = 1;
	if (toDelete && toDelete->parent)
	{
		CoreNode* toDeleteChild = toDelete->parent->child;

		CoreNode* tempNext = 0;
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