// Nodes.h: interface for the Nodes class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NODES_H__2042AE37_864B_4DDD_B546_D1118B98AC5D__INCLUDED_)
#define AFX_NODES_H__2042AE37_864B_4DDD_B546_D1118B98AC5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

class SYSCORE_API ANode  
{
public:
	ANode() { }

	virtual void genAge(struct AgeServer *);
	virtual void genAgeNode(struct AgeServer *);
	virtual int getAgeNodeType();
};

#include "RandomAccessStream.h"

class SYSCORE_API CoreNode 
	: public ANode
{
public:
	// 4 for vtbl ptr
	char * name; // this + 4
	CoreNode * parent;  // this + 8
	CoreNode * next;	 // this + 12 (C)
	CoreNode * child; // this + 16 (10)

	CoreNode(char * name = "CoreNode")
	{
		this->initCore(name);
	}

	virtual void write (RandomAccessStream *) {}
	virtual void read  (RandomAccessStream *) {}
	virtual int getAgeNodeType() { return 2; }

	CoreNode * Next   ()				{ return this->next;  }
	void	   Next   (CoreNode * set)  { this->next = set;   }
	CoreNode * Child  ()				{ return this->child; }
	void	   Child  (CoreNode * set)	{ this->child = set;  }
	char	 * Name   ()				{ return this->name;  }
	CoreNode * Parent ()				{ return this->parent;}

	int getChildCount();

	void initCore(char * name);
	void setName(char * name);

	void add(CoreNode *);
	void del();

	void load(char *, char *, unsigned __int32); // TODO

	void genWrite(struct AgeServer *);			 // TODO
	void genRead (struct AgeServer *);			 // TODO
	virtual void genAgeNode(struct AgeServer *){}// TODO
	virtual void genAge(struct AgeServer *){}	 // TODO
};

class SYSCORE_API Node
	: public CoreNode
{
public:
	//Var
	int type;
	int flags;
	int dword1c;

	//Functions
	Node(char * name = "<Node>") : CoreNode(name) { /*this->init(name)*/ }

};

static unsigned char foundNode;
static CoreNode * unkNode;

class SYSCORE_API NodeMgr
{
	//Var
	int unk;
	CoreNode firstnode;

	// Functions
	NodeMgr() { unk = 0; }
	~NodeMgr() {}

	CoreNode * findNode(char *, CoreNode *);
	CoreNode * firstNode() { return &this->firstnode; }
	void recFindNode(CoreNode *, char *);
};

#endif // !defined(AFX_NODES_H__2042AE37_864B_4DDD_B546_D1118B98AC5D__INCLUDED_)
