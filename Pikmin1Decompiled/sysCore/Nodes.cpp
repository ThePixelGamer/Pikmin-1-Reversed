// Nodes.cpp: implementation of the various node classes.
//
//////////////////////////////////////////////////////////////////////

#include "Nodes.h"

//////////////////////////////////////////////////////////////////////
// ANode class functions
//////////////////////////////////////////////////////////////////////
void ANode::genAge(struct AgeServer *) {}
void ANode::genAgeNode(struct AgeServer *) {}
int ANode::getAgeNodeType() { return 0; }



void CoreNode::initCore(char * name)
{
	this->parent = 0;
	this->next = 0;
	this->child = 0;
	this->setName(name);
}

void CoreNode::setName(char * nme)
{
	this->name = nme;
}

void CoreNode::add(CoreNode * toAdd)
{
	CoreNode * temp = this->child;

	if (temp)
	{
		while (temp->next)
			temp = temp->next;
		temp->next = toAdd;
	}
	else
	{
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