#include "Nodes.h"

//////////////////////////////////////////////////////////////////////
// ANode class functions
//////////////////////////////////////////////////////////////////////
void ANode::genAge(struct AgeServer *) {}
void ANode::genAgeNode(struct AgeServer *) {}
int ANode::getAgeNodeType() { return 0; }

//////////////////////////////////////////////////////////////////////
// CoreNode class functions
//////////////////////////////////////////////////////////////////////
void CoreNode::initCore(char* nme) {
	this->parent = 0;
	this->next = 0;
	this->child = 0;
	this->setName(nme);
}

void CoreNode::setName(char* nme){
	this->name = nme;
}

void CoreNode::add(CoreNode* toAdd) {
	if(this->child) {
		while (this->child->next)
			this->child = this->child->next;
		this->child->next = toAdd;
	} else {
		this->child = toAdd;
	}

	toAdd->parent = this;
}

void CoreNode::del()
{
  if ( this->parent )
  {
    CoreNode * parChild = this->parent->child;
    CoreNode * oldChild = 0;
    while ( parChild )
    {
      if ( parChild == this )
      {
        if ( oldChild )
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
	for (CoreNode *temp = this->child; temp; temp = temp->next)
		count++;
	return count;
}

//////////////////////////////////////////////////////////////////////
// NodeMgr class functions
//////////////////////////////////////////////////////////////////////

CoreNode * NodeMgr::findNode(char * a1, CoreNode * a2)
{
	unkNode = 0;
	foundNode = 0;
	if (!a2)
		a2 = this->firstNode();
	this->recFindNode(a2, a1);
	return unkNode;
}

void NodeMgr::recFindNode(CoreNode * toFind, char * name)
{ 
	if ( !foundNode )
	{
		for ( CoreNode * i = toFind; i; i = i->Next() )
		{
			if ( !strcmp(name, i->name) )
			{
				foundNode = 1;
				unkNode = i;
				return;
			}
		  if ( i->child )
			  this->recFindNode(i->child, name);
		}
	}
}